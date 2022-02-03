#pragma once

#include <QJsonDocument>

#include "Net/Parsing.h"
#include "Net/Entities/Income/Income.h"
#include "Net/Entities/Income/IncomeCategory.h"
#include "Net/Tools/Formatters/Income/IncomeCategoryJSONFormatter.h"

template <typename Entity>
class IncomeJSONFormatter
{
	using IncomeCategoryType = IncomeCategory<typename Entity::StringType>;
public:
	QJsonDocument Format(Entity& income)
	{
		IncomeCategoryJSONFormatter<IncomeCategoryType> category_formatter;
		QJsonObject json;

		WriteId(json, "id", income.id);
		json["category"] = category_formatter.Format(income.category);

		WriteString(json, "name",  income.name);
		WriteMoney(json, "amount", income.amount);

		WriteString(json, "add_time",  income.add_time);
		WriteString(json, "expiration_time",  income.expiration_time);

		return QJsonDocument{json};
	}
};
