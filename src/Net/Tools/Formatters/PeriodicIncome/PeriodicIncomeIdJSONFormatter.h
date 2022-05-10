#pragma once

#include <QJsonDocument>

#include "Net/Entities/PeriodicIncome/PeriodicIncomeId.h"

class PeriodicIncomeIdJSONFormatter
{
public:
	QJsonObject Format(const PeriodicIncomeId& income_id);
};
