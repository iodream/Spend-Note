#pragma once

#include "Net/Types.h"

template<typename T>
struct ExpensePerDayBase
{
	T day;
	Money amount;
};
