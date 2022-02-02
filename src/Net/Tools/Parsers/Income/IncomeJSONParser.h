#pragma once

#include <QJsonObject>
#include <QJsonDocument>

#include "Net/Entities/Income/Income.h"
#include "Net/Parsing.h"
#include "IncomeCategoryJSONParser.h"

template <typename T>
class IncomeJSONParser
{
public:
	T Parse(const QJsonObject& json)
	{
		T income;
		QJsonObject category_json;
		IncomeCategoryJSONParser<T> category_json_parser;

		SafeReadId(json, "id", income.id);

		SafeReadObject(json, "category", category_json);
		category_json_parser.Parse(category_json);

		SafeReadMoney(json, "amount", income.amount);
		SafeReadString(json, "name", income.name);
		SafeReadString(json, "add_time", income.add_time);
		SafeReadString(json, "expiration_time", income.expiration_time);
		return income;
	}
};
