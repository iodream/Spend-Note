#include <QJsonObject>

#include "Net/Parsing.h"
#include "ExpensePercentagePerCategoryJSONParser.h"

ExpensePercentagePerCategory ExpensePercentagePerCategoryJSONParser::Parse(const QJsonObject& json)
{
	ExpensePercentagePerCategory expense;
	SafeReadId(json, "category_id", expense.category_id);
	SafeReadNumber(json, "percentage", expense.percentage);
	return expense;
}
