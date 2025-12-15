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
    }
}