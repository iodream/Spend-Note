#pragma once

#include <QJsonDocument>

#include "Net/Parsing.h"

template <template<typename> typename CategoryFormatter, typename Income>
class IncomeJSONFormatterBase
{
	using IncomeCategory = typename Income::CategoryType;
public:
	QJsonObject Format(const Income& income)
	{
		CategoryFormatter<IncomeCategory> category_formatter;
		QJsonObject json;

		WriteId(json, "id", income.id);
		WriteId(json, "user_id", income.user_id);
		json["category"] = category_formatter.Format(income.category);

		WriteString(json, "name",  income.name);
		WriteMoney(json, "amount", income.amount);

		WriteString(json, "add_time",  income.add_time);
		WriteString(json, "expiration_time",  income.expiration_time);

		return json;
	}
};
