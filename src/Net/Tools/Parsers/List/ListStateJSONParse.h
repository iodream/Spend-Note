#pragma once
#include <QJsonObject>

#include "../Net/Entities/ListState.h"
#include "../Net/Parsing.h"

template<typename Entity>
class ListStateJSONParser
{
public:
	Entity Parser(const QJsonObject& obj)
	{
		Entity state;

		SafeReadId(obj, "id", state.id);
		SafeReadString(obj, "name", state.name);

		return state;
	}
};
