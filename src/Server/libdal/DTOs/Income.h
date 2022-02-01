#pragma once

#include <string>
#include <optional>
#include "Types.h"

struct Income
{
	IdType id;
	IdType user_id;
	std::string name;
	Money amount;
	IdType category_id;
	std::string add_time;
	std::optional<std::string> expiration_time;
};
