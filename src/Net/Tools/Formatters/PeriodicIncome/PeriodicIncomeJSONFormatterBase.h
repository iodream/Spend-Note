#pragma once

#include <QJsonDocument>

#include "Net/Parsing.h"

template <template<typename> typename CategoryFormatter, typename PeriodicIncome>
class PeriodicIncomeJSONFormatterBase
{
	using IncomeCategory = typename PeriodicIncome::CategoryType;
public:
	QJsonObject Format(const PeriodicIncome& income)
	{
		CategoryFormatter<IncomeCategory> category_formatter;
		QJsonObject json;
		auto category = income.category;
		WriteId(json, "id", income.id);

		json["category"] = category_formatter.Format(category);

		WriteString(json, "name", income.name);
		WriteBigInt(json, "amount", income.amount);

		WriteId(json, "period_id", income.period_id);
		WriteString(json, "next_add_date", income.next_add_date);
		WriteString(json, "add_until", income.add_until);

		return json;
	}
};
