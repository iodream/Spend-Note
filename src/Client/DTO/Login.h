#pragma once

#include <string>

struct LoginInDTO
{
    std::string login;
    std::string password;
};

struct LoginOutDTO
{
    std::string status;
    std::string reason;
};

