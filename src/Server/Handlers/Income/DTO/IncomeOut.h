#pragma once

#include <string>
#include "../../AuthorizedHandler.h"
#include "IncomeCategory.h"

struct IncomeOut
{
	IdType id;
	IdType user_id;
	std::string name;
	double amount;
	std::string category_name;
	std::string add_time;
	std::string expiration_time;
};


