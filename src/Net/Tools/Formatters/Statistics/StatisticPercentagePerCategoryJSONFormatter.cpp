#include <QJsonObject>

#include "StatisticPercentagePerCategoryJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject StatisticPercentagePerCategoryJSONFormatter::Format(const StatisticPercentagePerCategory& expense)
{
	QJsonObject json;
	WriteId(json, "category_id", expense.category_id);
	WriteNumber(json, "percentage", expense.percentage);
	return json;
}
