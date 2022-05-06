#pragma once

#include "QJsonDocument"
#include "Net/Entities/PeriodicIncome/PeriodicIncomeId.h"

class PeriodicIncomeIdJSONParser
{
public:
	PeriodicIncomeId Parse(const QJsonObject& json);
};
