#pragma once

#include "QJsonDocument"
#include "Net/Entities/Statistics/StatisticPerCategory.h"

class StatisticPerCategoryJSONParser
{
public:
	StatisticPerCategory Parse(const QJsonObject& json);
};
