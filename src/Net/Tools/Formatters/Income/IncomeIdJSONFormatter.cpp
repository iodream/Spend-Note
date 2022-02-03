#include "IncomeIdJSONFormatter.h"

QJsonDocument IncomeIdJSONFormatter::Format(IncomeId& income_id)
{
	QJsonObject json;
	WriteId(json, "id", income_id.id);
	return QJsonDocument{json};
}
