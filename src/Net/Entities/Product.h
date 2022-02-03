#pragma once

#include "../libdal/Types.h"

#include "ProductCategory.h"

template <typename T>
struct Product
{
	using StringType = T;
	IdType id;
	IdType list_id;
	ProductCategory<T> category;
	bool is_bought;
	T name;
	BigInt amount;
	Money price;
	int priority;
	T add_date;
	T purchase_date;
	T buy_until_date;
};
