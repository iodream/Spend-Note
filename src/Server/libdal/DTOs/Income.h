#pragma once

#include <string>
#include <optional>
#include "Types.h"

struct Income
{
	IdType income_id;
	IdType user_id;
	std::string name;
	double amount;
	IdType category_id;
	std::string add_time;
    std::optional<std::string> expiration_time;
};
