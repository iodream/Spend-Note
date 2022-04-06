#pragma once

#include <QJsonDocument>

#include "Net/Entities/Statistics/StatisticPercentagePerCategory.h"

class StatisticPercentagePerCategoryJSONFormatter
{
public:
	QJsonObject Format(const StatisticPercentagePerCategory& expense);
};
