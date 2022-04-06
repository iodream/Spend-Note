#pragma once

#include "Net/Types.h"

template<typename T>
struct StatisticPerDayBase
{
	T day;
	Money amount;
};
