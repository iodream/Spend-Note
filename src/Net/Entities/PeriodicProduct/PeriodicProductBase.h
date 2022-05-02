#pragma once

#include "Net/Types.h"

template <template<typename> typename Category, typename T>
struct PeriodicProductBase
{
	using StringType = T;
	using CategoryType = Category<T>;

	IdType id;
	IdType list_id;
	Category<T> category;
	T name;
	BigInt amount;
	Money price;
	BigInt priority;

	IdType period_id;
	T next_add_date;
	T add_until;
};
