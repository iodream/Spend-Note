#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include "Net/Entities/Income/IncomeId.h"
#include "Net/Parsing.h"

class IncomeIdJSONFormatter
{
	QJsonDocument Format(IncomeId& income_id)
	{
		QJsonObject json;
		WriteId(json, "id", income_id.id);
		return QJsonDocument{json};
	}
};
