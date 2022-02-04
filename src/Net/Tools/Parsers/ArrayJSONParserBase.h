#pragma once

#include <QJsonObject>
#include <QJsonDocument>

#include "Net/Parsing.h"

template <typename ItemParser, typename Item>
class ArrayJSONParserBase
{
public:
	std::vector<Item> Parse(const QJsonArray& array)
	{
		std::vector<Item> items;
		ItemParser parser;

		for (const QJsonValue& item : array)
		{
			items.push_back(parser.Parse(item));
		}

		return items;
	}
};
