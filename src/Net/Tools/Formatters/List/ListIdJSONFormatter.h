#pragma once
#include <QJsonObject>

#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"

template<class Entity> // rename
class ListIdJSONFormatter
{
public:
	QJsonDocument Format(const List<Entity>& list)
	{
		QJsonObject json;
		WriteId(json, "id", list.id);
		return QJsonDocument{json};
	};
};
