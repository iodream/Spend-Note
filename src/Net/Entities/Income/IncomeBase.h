#pragma once

#include "Net/Types.h"

template <template<typename> typename Category, typename T>
struct IncomeBase
{
	using StringType = T;
	using CategoryType = Category<T>;

	IdType id;
	IdType user_id;
	Category<T> category;
	T name;
	Money amount;
	T add_time;
	T expiration_time;
};
