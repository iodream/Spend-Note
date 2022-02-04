#pragma once

#include "Net/Types.h"

template <template<typename> typename Category, typename T>
struct ProductBase
{
	using StringType = T;
	using CategoryType = Category<T>;

	IdType id;
	IdType list_id;
	Category<T> category;
	bool is_bought;
	T name;
	BigInt amount;
	Money price;
	BigInt priority;
	T add_date;
	T purchase_date;
	T buy_until_date;
};
