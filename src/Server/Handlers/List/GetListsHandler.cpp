#include <QJsonArray>

#include "GetListsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "Utils.h"

GetListsHandler::GetListsHandler()
{
}

Net::Response GetListsHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto db_lists = m_facade->GetAllLists(user_id);

	std::vector<List> lists;
	for (const db::List& db_list : db_lists) {
		auto state = m_facade->GetListStateById(db_list.state_id);
		if (!state.has_value())
		{
			throw InternalError(std::string("No list state with id:") + std::to_string(db_list.state_id));
		}
		auto list = ToNetList(db_list, state.value());
		lists.push_back(list);
	}

	return FormJSONResponse(m_formatter.Format(lists));
}
