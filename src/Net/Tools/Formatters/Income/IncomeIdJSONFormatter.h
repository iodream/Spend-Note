#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/Income/IncomeId.h"
#include "Net/Parsing.h"

class IncomeIdJSONFormatter
{
public:
	QJsonObject Format(const IncomeId& income_id);
};
