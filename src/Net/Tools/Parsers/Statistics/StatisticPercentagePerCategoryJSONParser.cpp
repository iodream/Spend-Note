#include <QJsonObject>

#include "Net/Parsing.h"
#include "StatisticPercentagePerCategoryJSONParser.h"

StatisticPercentagePerCategory StatisticPercentagePerCategoryJSONParser::Parse(const QJsonObject& json)
{
	StatisticPercentagePerCategory expense;
	SafeReadId(json, "category_id", expense.category_id);
	SafeReadNumber(json, "percentage", expense.percentage);
	return expense;
}
