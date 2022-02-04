#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template<class State>
class ListStateJSONFormatterBase
{
public:
	QJsonObject Format(const State& state)
	{
		QJsonObject json;
		WriteId(json, "id", state.id);
		WriteString(json, "name", state.name);
		return json;
	};
};
