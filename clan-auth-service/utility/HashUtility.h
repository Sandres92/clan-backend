#pragma once

#include <string>

namespace clan
{
    static std::string hashPasword(const std::string &password)
    {
        return "hash_" + password;
    }
}