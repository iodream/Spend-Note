#pragma once

#include <string>
#include "Types.h"

namespace db
{
	struct User
	{
		IdType id;
		std::string login;
		std::string password;
		std::string salt;
	};
}
