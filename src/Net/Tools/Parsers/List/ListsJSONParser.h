#pragma once
#include <QJsonObject>

#include "ListJSONParser.h"
#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"

template <typename Entity>
class ListsJSONParser
{
public:
	std::vector<Entity> Parse(const QJsonDocument& obj)
	{
		std::vector<Entity> lists;
		ListJSONParser<Entity> list_parser{};

		for(const auto& el : obj.array())
		{
			lists.push_back(list_parser.Parse(el.toObject()));
		}

		return lists;
	};
};
