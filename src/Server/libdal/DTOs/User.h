#pragma once

#include <string>
#include "Types.h"

namespace db
{
	struct User
	{
		IdType id;
		std::string login;
		std::string password_hash;
		std::string salt;
	};
}
