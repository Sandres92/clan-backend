#include "UserController.h"
#include "models/CreateUser.h"

using namespace clan::v1;

namespace clan
{
    namespace v1
    {
        void UserController::Register(clan::v1::CreateUser &&user,
                                      std::function<void(const drogon::HttpResponsePtr &)> &&callback) const
        {
            LOG_DEBUG << "UserController::Register";

            auto client = drogon::app().getDbClient();

            client->execSqlAsync("INSERT INTO users (username, password_hash, description) VALUES($1,$2,$3)", [callback](const drogon::orm::Result &result)
                                 {
                                    Json::Value ret;
                                    ret["result"] = "ok";
                                    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
                                    callback(resp); }, [callback](const drogon::orm::DrogonDbException &e)
                                 { 
                                    Json::Value ret;
                                    ret["result"] = "error";
                                    ret["msg"] = e.base().what();

                                    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
                                            callback(resp); }, user.username, user.password, user.description);
        }

        void UserController::Login(clan::v1::CreateUser &&user,
                                   std::function<void(const drogon::HttpResponsePtr &)> &&callback) const
        {
            LOG_DEBUG << "UserController::Login";

            auto client = drogon::app().getDbClient();
            client->execSqlAsync("SELECT id,password_hash FROM users WHERE username=$1", [callback, user](const drogon::orm::Result &result)
                                 {
                                     if (result.empty())
                                     {
                                         Json::Value ret;
                                         ret["result"] = "error";
                                         ret["msg"] = "User not found";

                                        auto resp = HttpResponse::newHttpJsonResponse(ret);
                                        callback(resp);
                                        return;
                                     }

                                     const auto &row = result[0];
                                     std::string dbPassword = row["password_hash"].as<std::string>();

                                     if (dbPassword == user.password)
                                     {
                                        std::string token = drogon::utils::getUuid();
                                        auto redis = drogon::app().getRedisClient();
                                         std::string redisKey = "auth:token:" + token;

                                        redis->execCommandAsync(
                                            [](const drogon::nosql::RedisResult &r){ /* можно логировать успех */ },
                                            [](const drogon::nosql::RedisException &e){ LOG_ERROR << "Redis error: " << e.what(); },
                                            "SETEX %s %d %d", redisKey, "3600", std::to_string(row["id"].as<int>())  // row["id"] = user_id из БД
                                        );

                                         Json::Value ret;
                                         ret["result"] = "ok";
                                         ret["token"] = token;

                                         auto resp = HttpResponse::newHttpJsonResponse(ret);
                                         callback(resp);
                                     }
                                     else
                                     {
                                         Json::Value ret;
                                         ret["result"] = "error";
                                         ret["token"] = "Wrong password";

                                         auto resp = HttpResponse::newHttpJsonResponse(ret);
                                         callback(resp);
                                     } }, [callback](const drogon::orm::DrogonDbException &e)
                                 {
                                    Json::Value ret;
                                    ret["result"] = "error";
                                    ret["msg"] = e.base().what();

                                    auto resp = HttpResponse::newHttpJsonResponse(ret);                                    
                                    callback(resp); }, user.username

            );
        }
    }
}