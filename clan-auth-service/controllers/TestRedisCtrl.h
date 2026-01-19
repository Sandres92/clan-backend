#pragma once

#include <drogon/HttpSimpleController.h>
#include <drogon/nosql/RedisClient.h>

using namespace drogon;

class TestRedisCtrl : public drogon::HttpSimpleController<TestRedisCtrl>
{
public:
    void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;

    PATH_LIST_BEGIN
    // list path definitions here

    // example
    // PATH_ADD("/path","filter1","filter2",HttpMethod1,HttpMethod2...);

    PATH_ADD("/", Get, Post);
    PATH_ADD("/test_redis", Get);
    PATH_LIST_END
};
