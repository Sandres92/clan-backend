#include "TestCtrl.h"

void TestCtrl::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{

    drogon::nosql::RedisClientPtr redisClient = drogon::app().getRedisClient();
    redisClient->execCommandAsync(
        [](const drogon::nosql::RedisResult &r)
        {
            LOG_INFO << "Redis PING response: " << r.asString();
        },
        [](const drogon::nosql::RedisException &e)
        {
            LOG_ERROR << "Redis PING failed: " << e.what();
        },
        "PING");

    // write your application logic here
    auto resp = drogon::HttpResponse::newHttpResponse();
    // NOTE: The enum constant below is named "k200OK" (as in 200 OK), not "k2000K".
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    resp->setBody("Hello World!");
    callback(resp);
}
