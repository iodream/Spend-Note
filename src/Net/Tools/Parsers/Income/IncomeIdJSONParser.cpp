#include "IncomeIdJSONParser.h"

IncomeId IncomeIdJSONParser::Parse(const QJsonObject& json)
{
	IncomeId income_id;
	SafeReadId(json, "id", income_id.id);
	return income_id;
}
