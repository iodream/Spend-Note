#pragma once

#include <QJsonObject>
#include <QJsonDocument>

#include "Net/Entities/Income/Income.h"
#include "Net/Parsing.h"
#include "IncomeJSONParser.h"

template <typename Entity>
class IncomeArrayJSONParser
{
public:
	std::vector<Entity> Parse(const QJsonDocument& json)
	{
		std::vector<Entity> incomes;
		IncomeJSONParser<Entity> parser;

		QJsonArray array = json.array();

		for(const QJsonValue& income : array)
		{
			incomes.push_back(parser.Parse(income));
		}
		return incomes;
		}
};
