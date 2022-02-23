#include <QJsonObject>

#include "Net/Parsing.h"
#include "ExpensePerCategoryJSONParser.h"

ExpensePerCategory ExpensePerCategoryJSONParser::Parse(const QJsonObject& json)
{
	ExpensePerCategory expense;
	SafeReadId(json, "category_id", expense.category_id);
	SafeReadMoney(json, "amount", expense.amount);
	return expense;
}
