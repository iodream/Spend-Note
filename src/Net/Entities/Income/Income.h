#pragma once

#include "Server/libdal/Types.h"
#include "IncomeCategory.h"

template <typename T>
struct Income
{
	using StringType = T;
	db::IdType id;
	IncomeCategory<T> category;
	T name;
	db::Money amount;
	T add_time;
	T expiration_time;
};
