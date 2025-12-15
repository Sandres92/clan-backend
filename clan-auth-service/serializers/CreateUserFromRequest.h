#include "../models/CreateUser.h"

#include <drogon/HttpRequest.h>
#include <jsoncpp/json/json.h>

namespace drogon
{
    template <>
    inline clan::v1::CreateUser fromRequest(const drogon::HttpRequest &req)
    {
        auto json = req.getJsonObject();
        clan::v1::CreateUser user;
        if (json)
        {
            user.username = (*json)["username"].asString();
            user.password = (*json)["password"].asString();
            user.description = (*json)["description"].asString();
        }
        return user;
    }
}