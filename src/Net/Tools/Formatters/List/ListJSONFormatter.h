#pragma once
#include <QJsonObject>

#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"
#include "ListStateJSONFormatter.h"

template<class Entity>
class ListJSONFormatter
{
	using ListStateType = ListState<typename Entity::StringType>;
public:
	QJsonDocument Format(const List<Entity>& list)
	{
		QJsonObject json, tmp_json;
		ListStateJSONFormatter<ListStateType> state_formatter{};

		WriteId(json, "id", list.id);
		WriteId(json, "owner_id", list.owner_id);
		WriteString(json, "name", list.name);

		json["state"] = state_formatter.Format(list.state).object();

		return QJsonDocument{json};
	}
};
