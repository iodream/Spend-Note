#pragma once

#include <string>

#include "Types.h"
#include "ProductCategory.h"

struct Product
{
	IdType id;
	IdType list_id;
	ProductCategory category;
	bool is_bought;
	std::string name;
	BigInt amount;
	Money price;
	int priority;
	std::string add_date;
	std::string purchase_date;
	std::string buy_until_date;
};
