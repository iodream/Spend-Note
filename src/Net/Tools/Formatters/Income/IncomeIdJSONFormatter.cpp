#include "IncomeIdJSONFormatter.h"

QJsonObject IncomeIdJSONFormatter::Format(const IncomeId& income_id)
{
	QJsonObject json;
	WriteId(json, "id", income_id.id);
	return json;
}
