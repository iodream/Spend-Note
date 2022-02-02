#pragma once

#include "Types.h"
#include "ListState.h"

template<typename T>
struct List
{
	using StringType = T;

	IdType id;
	T name;
	IdType owner_id;
	ListState<T> state;
};
