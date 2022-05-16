#include <QJsonObject>

#include "PeriodicIncomeIdJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject PeriodicIncomeIdJSONFormatter::Format(const PeriodicIncomeId& income_id)
{
	QJsonObject json;
	WriteId(json, "id", income_id.id);
	return json;
}
