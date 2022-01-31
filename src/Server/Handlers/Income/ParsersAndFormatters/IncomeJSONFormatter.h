#pragma once

#include "../DTO/IncomeId.h"
#include "../DTO/IncomeOut.h"

using Incomes = std::vector<IncomeOut>;

class IncomeJSONFormatter
{
public:
	QJsonDocument Format(const IncomeId& dto);

	QJsonObject Format(const IncomeOut& income);
	QJsonDocument Format(const Incomes& incomes);
};
