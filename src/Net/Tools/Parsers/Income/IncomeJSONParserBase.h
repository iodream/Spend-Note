#pragma once

#include <QJsonObject>
#include <QJsonDocument>

#include "Net/Parsing.h"

template <template<typename> typename CategoryParser, typename Income>
class IncomeJSONParserBase
{
	using IncomeCategory = typename Income::CategoryType;
public:
	Income Parse(const QJsonObject& json)
	{
		Income income;
		QJsonObject category_json;
		CategoryParser<IncomeCategory> category_json_parser;

		SafeReadId(json, "id", income.id);
		SafeReadId(json, "user_id", income.user_id);

		SafeReadObject(json, "category", category_json);
		income.category = category_json_parser.Parse(category_json);

		SafeReadMoney(json, "amount", income.amount);
		SafeReadString(json, "name", income.name);
		SafeReadString(json, "add_time", income.add_time);
		SafeReadString(json, "expiration_time", income.expiration_time);
		return income;
	}
};
