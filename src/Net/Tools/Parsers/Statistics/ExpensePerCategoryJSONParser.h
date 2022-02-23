#pragma once

#include "QJsonDocument"
#include "Net/Entities/Statistics/ExpensePerCategory.h"

class ExpensePerCategoryJSONParser
{
public:
	ExpensePerCategory Parse(const QJsonObject& json);
};
