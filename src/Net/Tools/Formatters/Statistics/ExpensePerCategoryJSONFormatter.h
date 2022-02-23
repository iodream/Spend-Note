#pragma once

#include <QJsonDocument>

#include "Net/Entities/Statistics/ExpensePerCategory.h"

class ExpensePerCategoryJSONFormatter
{
public:
	QJsonObject Format(const ExpensePerCategory& expense);
};
