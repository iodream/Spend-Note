#include <QJsonObject>

#include "Net/Parsing.h"
#include "PeriodicIncomeIdJSONParser.h"

PeriodicIncomeId PeriodicIncomeIdJSONParser::Parse(const QJsonObject& json)
{
	PeriodicIncomeId income_id;
	SafeReadId(json, "id", income_id.id);
	return income_id;
}
