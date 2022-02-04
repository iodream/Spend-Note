#pragma once
#include <QJsonObject>

#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"
#include "ListJSONFormatter.h"

template<class Entity>
class ListsJSONFormatter
{
public:
	QJsonDocument Format(const std::vector<Entity>& lists)
	{
		QJsonArray out_lists;
		ListJSONFormatter<Entity> list_formatter{};

		for (const auto& dto_item : lists)
		{
			out_lists.append(list_formatter.Format(dto_item).object());
		}

		return QJsonDocument{out_lists};
	};
};
