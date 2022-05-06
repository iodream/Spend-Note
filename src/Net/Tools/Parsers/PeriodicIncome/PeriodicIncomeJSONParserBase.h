#pragma once

#include "QJsonDocument"

#include "Net/Parsing.h"

template <template<typename> typename CategoryParser, typename PeriodicIncome>
class PeriodicIncomeJSONParserBase
{
	using IncomeCategory = typename PeriodicIncome::CategoryType;
public:
	PeriodicIncome Parse(const QJsonObject& json)
	{
		PeriodicIncome income;
		QJsonObject category_json;
		CategoryParser<IncomeCategory> category_parser;

		SafeReadId(json, "id", income.id);

		SafeReadObject(json, "category", category_json);
		income.category = category_parser.Parse(category_json);

		SafeReadString(json, "name", income.name);
		SafeReadBigInt(json, "amount", income.amount);

		SafeReadId(json, "period_id", income.period_id);
		SafeReadString(json, "next_add_date", income.next_add_date);
		SafeReadString(json, "add_until", income.add_until);

		return income;
	}
};
