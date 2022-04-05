#pragma once

#include "QJsonDocument"
#include "Net/Entities/Statistics/ExpensePercentagePerCategory.h"

class ExpensePercentagePerCategoryJSONParser
{
public:
	ExpensePercentagePerCategory Parse(const QJsonObject& json);
};
