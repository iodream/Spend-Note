#pragma once

#include <QJsonDocument>

#include "Net/Entities/Statistics/StatisticPerCategory.h"

class StatisticPerCategoryJSONFormatter
{
public:
	QJsonObject Format(const StatisticPerCategory& expense);
};
