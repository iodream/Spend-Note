#include "IncomeIdUtils.h"

QJsonDocument FormatIncomeId(const IncomeId& income_id)
{
	QJsonObject json;
	json["id"] = income_id.id;
	return QJsonDocument{json};
}
