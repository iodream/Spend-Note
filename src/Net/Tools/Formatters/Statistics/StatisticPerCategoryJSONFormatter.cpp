#include <QJsonObject>

#include "StatisticPerCategoryJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject StatisticPerCategoryJSONFormatter::Format(const StatisticPerCategory& expense)
{
	QJsonObject json;
	WriteId(json, "category_id", expense.category_id);
	WriteMoney(json, "amount", expense.amount);
	return json;
}
