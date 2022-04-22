#pragma once

#include <string>
#include "Types.h"

namespace db
{
	struct User
	{
		IdType id;
		std::string email;
		std::string password;
		bool verified;
	};
}
