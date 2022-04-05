#include <QJsonObject>

#include "ExpensePerCategoryJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject ExpensePerCategoryJSONFormatter::Format(const ExpensePerCategory& expense)
{
	QJsonObject json;
	WriteId(json, "category_id", expense.category_id);
	WriteMoney(json, "amount", expense.amount);
	return json;
}
