#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template <template<typename> typename StateParser, typename List>
class ListJSONParserBase
{
	using ListState = typename List::StateType;
public:
	List Parse(const QJsonObject& obj)
	{
		List list;
		QJsonObject state_json;
		StateParser<ListState> state_parser{};

		SafeReadId(obj, "id", list.id);
		SafeReadString(obj, "name", list.name);
		SafeReadId(obj, "owner_id", list.owner_id);

		SafeReadObject(obj, "state", state_json);
		list.state = state_parser.Parse(state_json);

		return list;
	}
};
