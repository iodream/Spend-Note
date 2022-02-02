#pragma once

#include "../libdal/Types.h"

template <typename T>
struct ProductCategory
{
	using StringType = T;
	IdType id;
	T name;
};
