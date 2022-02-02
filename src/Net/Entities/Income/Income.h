#pragma once

#include "Server/libdal/Types.h"
#include "IncomeCategory.h"

template <typename T>
struct Income
{
	IdType id;
	IncomeCategory<T> category;
	T name;
	Money amount;
	T add_time;
	T expiration_time;
};
