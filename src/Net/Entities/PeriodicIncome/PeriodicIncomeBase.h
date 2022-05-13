#pragma once

#include "Net/Types.h"

template <template<typename> typename Category, typename T>
struct PeriodicIncomeBase
{
	using StringType = T;
	using CategoryType = Category<T>;

	IdType id;
	Category<T> category;
	T name;
	Money amount;

	IdType period_id;
	T next_add_date;
	T add_until;
};
