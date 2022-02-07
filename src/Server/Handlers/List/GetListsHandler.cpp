#include <QJsonArray>

#include "GetListsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"

GetListsHandler::GetListsHandler()
{
}

std::vector<List> GetListsHandler::ToNetLists(const Lists &lists)
{
	std::vector<List> net_lists;
	List list;
	for (const auto db_list : lists)
	{
		list.id = db_list.first.id;
		list.name = db_list.first.name;
		list.owner_id = db_list.first.owner_id;
		list.state.id = db_list.second.id;
		list.state.name = db_list.second.name;
		net_lists.push_back(list);
	}
	return net_lists;
}

Net::Response GetListsHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto lists = m_facade->GetAllLists(user_id);

	Lists out_dto;
	for (const db::List& list : lists) {
		auto state = m_facade->GetListStateById(list.state_id);
		out_dto.push_back({list, state.value()});
	}
	auto net_lists = ToNetLists(out_dto);
	return FormJSONResponse(m_formatter.Format(net_lists));
}
