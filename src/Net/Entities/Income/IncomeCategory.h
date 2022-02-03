#pragma once

#include "Server/libdal/Types.h"

template <typename T>
struct IncomeCategory
{
	using StringType = T;
	IdType id;
	T name;
};
