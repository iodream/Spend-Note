#include <QJsonObject>

#include "Net/Parsing.h"
#include "StatisticPerCategoryJSONParser.h"

StatisticPerCategory StatisticPerCategoryJSONParser::Parse(const QJsonObject& json)
{
	StatisticPerCategory expense;
	SafeReadId(json, "category_id", expense.category_id);
	SafeReadMoney(json, "amount", expense.amount);
	return expense;
}
