#pragma once

#include <string>
#include "Types.h"

struct Income
{
	idType income_id;
	idType user_id;
    std::string name;
    double amount;
	idType category_id;
	std::string add_time;
	std::string expoiration_time;
};
