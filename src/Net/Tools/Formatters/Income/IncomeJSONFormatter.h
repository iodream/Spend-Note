#pragma once

#include <QJsonDocument>

#include "Net/Parsing.h"
#include "Net/Entities/Income/Income.h"
#include "Net/Entities/Income/IncomeCategory.h"

template <typename T>
class IncomeJSONFormatter
{
public:
	QJsonDocument Format(Income<T>& income)
	{
		QJsonObject json, category;

		WriteId(json, "id", income.id);
		json["category"] = FormatIncomeCategory(income.category);

		WriteString(json, "name",  income.name);
		WriteMoney(json, "amount", income.amount);

		WriteString(json, "add_time",  income.add_time);
		WriteString(json, "expiration_time",  income.expiration_time);

		return QJsonDocument{json};
	}
};
