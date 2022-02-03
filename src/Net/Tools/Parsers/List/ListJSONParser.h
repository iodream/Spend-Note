#pragma once
#include <QJsonObject>

#include "ListStateJSONParse.h"
#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"

template <typename Entity>
class ListJSONParser
{
	using ListStateType = ListState<typename Entity::StringType>;
public:
	Entity Parse(const QJsonObject& obj)
	{
		Entity list;
		QJsonObject state_json;
		ListStateJSONParser<ListStateType> state_parser{};

		SafeReadNumber(obj, "id", list.id);
		SafeReadString(obj, "name", list.name);
		SafeReadNumber(obj, "owner_id", list.owner_id);

		SafeReadObject(obj, "state", state_json);

		list.state = state_parser.Parser(state_json);

		return list;
	}

private:
};
