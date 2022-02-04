#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template <template<typename> typename StateFormatter, typename List>
class ListJSONFormatterBase
{
	using ListState = typename List::StateType;
public:
	QJsonObject Format(const List& list)
	{
		QJsonObject json;
		StateFormatter<ListState> state_formatter{};

		WriteId(json, "id", list.id);
		WriteId(json, "owner_id", list.owner_id);
		WriteString(json, "name", list.name);

		json["state"] = state_formatter.Format(list.state);

		return json;
	}
};
