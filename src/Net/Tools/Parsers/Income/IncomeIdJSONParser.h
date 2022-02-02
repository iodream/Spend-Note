#pragma once

#include <QJsonObject>
#include <QJsonDocument>

#include "Net/Entities/Income/IncomeId.h"
#include "Net/Parsing.h"

class IncomeIdJSONParser
{
public:
	IncomeId Parse(const QJsonObject& json)
	{
		IncomeId income_id;
		SafeReadId(json, "id", income_id.id);
		return income_id;
	}
};
