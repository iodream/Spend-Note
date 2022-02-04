#pragma once

#include "Net/Types.h"

template <typename T>
struct ProductCategoryBase
{
	using StringType = T;
	IdType id;
	T name;
};
