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

QJsonDocument GetListsHandler::JSONFormatter::Format(const Lists& dto)
{
	SCOPED_LOGGER;
	QJsonArray json_array;
	for (const auto& dto_item : dto) {
		QJsonObject list;

		list["list_id"] = std::to_string(dto_item.first.id).c_str();
		list["owner_id"] = std::to_string(dto_item.first.owner_id).c_str();
		list["state_id"] = std::to_string(dto_item.first.state_id).c_str();
		list["name"] = dto_item.first.name.c_str();
		list["state"] = dto_item.second.c_str();

		json_array.append(list);
	}
	return QJsonDocument{json_array};
}

Net::Response GetListsHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto lists = m_facade->GetAllLists(user_id);

	JSONFormatter::Lists out_dto;
	for (const List& list : lists) {
		auto state = m_facade->GetListStateById(list.state_id);
		std::string state_name = (state) ? state->name : EMPTY_STD_STRING;
		out_dto.push_back({list, state_name});
	}

	return FormJSONResponse(m_formatter.Format(out_dto));
}
