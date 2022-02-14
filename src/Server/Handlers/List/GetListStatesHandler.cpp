#include <QJsonArray>

#include "GetListStatesHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "Utils.h"

GetListStatesHandler::GetListStatesHandler()
{
}

Net::Response GetListStatesHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto db_list_states = m_facade->GetAllListStates();
	std::vector<ListState> list_states;

	for (const db::ListState& db_list_state : db_list_states) {
		auto list_state = ToNetListState(db_list_state);
		list_states.push_back(list_state);
	}

	return FormJSONResponse(m_formatter.Format(list_states));
}
