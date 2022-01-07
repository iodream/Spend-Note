#pragma once

#include <string>

using IdType = long long int;

struct User
{
	IdType id;
    std::string login;
	std::string password;
};
