#pragma once

#include "../models/CreateUser.h"
#include "../serializers/CreateUserFromRequest.h"

#include <drogon/HttpController.h>

using namespace drogon;

namespace clan
{
    namespace v1
    {
        class UserController : public drogon::HttpController<UserController>
        {
        private:
        public:
            METHOD_LIST_BEGIN
            METHOD_ADD(UserController::Register, "/register", Post);
            METHOD_LIST_END

            void Register(clan::v1::CreateUser &&user,
                          std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;
        };
    }
}