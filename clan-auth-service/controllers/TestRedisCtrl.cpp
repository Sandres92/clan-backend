#include "TestRedisCtrl.h"

void TestRedisCtrl::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{

    drogon::nosql::RedisClientPtr redisClient = drogon::app().getRedisClient();
    redisClient->execCommandAsync(
        [callback](const drogon::nosql::RedisResult &r)
        {
            auto resp = drogon::HttpResponse::newHttpResponse();
            // NOTE: The enum constant below is named "k200OK" (as in 200 OK), not "k2000K".
            resp->setStatusCode(k200OK);
            resp->setContentTypeCode(CT_TEXT_HTML);
            resp->setBody(r.asString());
            callback(resp);

            LOG_INFO << "Redis PING response: " << r.asString();
        },
        [callback](const drogon::nosql::RedisException &e)
        {
            auto resp = drogon::HttpResponse::newHttpResponse();
            // NOTE: The enum constant below is named "k200OK" (as in 200 OK), not "k2000K".
            resp->setStatusCode(k200OK);
            resp->setContentTypeCode(CT_TEXT_HTML);
            resp->setBody("Redis PING failed!");
            callback(resp);

            LOG_ERROR << "Redis PING failed: " << e.what();
        },
        "PING");
}
