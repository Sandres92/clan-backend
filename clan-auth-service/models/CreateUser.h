#pragma once

#include <string>

namespace clan
{
    namespace v1
    {
        struct CreateUser
        {
            std::string username;
            std::string password;
            std::string description;
        };
    }
}