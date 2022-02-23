#include <QJsonObject>

#include "ExpensePercentagePerCategoryJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject ExpensePercentagePerCategoryJSONFormatter::Format(const ExpensePercentagePerCategory& expense)
{
	QJsonObject json;
	WriteId(json, "category_id", expense.category_id);
	WriteNumber(json, "percentage", expense.percentage);
	return json;
}
