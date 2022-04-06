#pragma once

#include "QJsonDocument"
#include "Net/Entities/Statistics/StatisticPercentagePerCategory.h"

class StatisticPercentagePerCategoryJSONParser
{
public:
	StatisticPercentagePerCategory Parse(const QJsonObject& json);
};
