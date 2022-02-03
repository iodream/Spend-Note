#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include "Net/Entities/Income/IncomeId.h"
#include "Net/Parsing.h"

class IncomeIdJSONFormatter
{
public:
	QJsonDocument Format(IncomeId& income_id);
};
