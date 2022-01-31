#pragma once

#include <string>
#include "../../AuthorizedHandler.h"
#include "IncomeCategory.h"

struct IncomeIn
{
	IdType id;
	IncomeCategoryIn category;
	std::string name;
	double amount;
	std::string add_time;
	std::optional<std::string> expiration_time;
};
