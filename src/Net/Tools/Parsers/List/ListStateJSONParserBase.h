#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template<class State>
class ListStateJSONParserBase
{
public:
	State Parser(const QJsonObject& obj)
	{
		State state;

		SafeReadId(obj, "id", state.id);
		SafeReadString(obj, "name", state.name);

		return state;
	}
};
