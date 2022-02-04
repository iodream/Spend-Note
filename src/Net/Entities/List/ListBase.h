#pragma once

#include "Net/Types.h"

template <template<typename> typename State, typename T>
struct ListBase
{
	using StringType = T;
	using StateType = State<T>;

	IdType id;
	T name;
	IdType owner_id;
	State<T> state;
};
