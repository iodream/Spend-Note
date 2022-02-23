#pragma once

#include <QJsonDocument>

#include "Net/Entities/Statistics/ExpensePercentagePerCategory.h"

class ExpensePercentagePerCategoryJSONFormatter
{
public:
	QJsonObject Format(const ExpensePercentagePerCategory& expense);
};
