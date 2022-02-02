#pragma once
#include <QJsonObject>

#include "../Net/Entities/ListState.h"
#include "../Net/Parsing.h"

template<class Entity>
class ListStateJSONFormatter
{
public:
	QJsonDocument Format(const ListState<Entity>& state)
	{
		QJsonObject json;
		WriteId(json, "id", state.id);
		WriteString(json, "name", state.name);
		return QJsonDocument{json};
	};
};
