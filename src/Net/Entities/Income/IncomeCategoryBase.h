#pragma once

#include "Net/Types.h"

template <typename T>
struct IncomeCategoryBase
{
	using StringType = T;
	IdType id;
	T name;
};
