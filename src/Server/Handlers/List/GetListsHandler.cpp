#include <QJsonArray>

#include "GetListsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"

GetListsHandler::GetListsHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

QJsonDocument GetListsHandler::JSONFormatter::Format(const Lists& dto)
{
	QJsonObject json;

	QJsonArray lists;
	for (const auto& dto_item : dto) {
		QJsonObject list;

		list["list_id"] = std::to_string(dto_item.first.list_id).c_str();
		list["owner_id"] = std::to_string(dto_item.first.owner_id).c_str();
		list["state_id"] = std::to_string(dto_item.first.state_id).c_str();
		list["name"] = dto_item.first.name.c_str();
		list["state"] = dto_item.second.c_str();

		lists.append(list);
	}
	json["lists"] = lists;

	return QJsonDocument{json};
}

Net::Response GetListsHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_GET) {

		auto lists = m_facade->GetAllLists(request.uid);

		JSONFormatter::Lists out_dto;
		for (const List& list : lists) {
			auto state = m_facade->GetListStateById(list.state_id);
			std::string state_name = (state) ? state->name : EMPTY_STD_STRING;
			out_dto.push_back({list, state_name});
		}

		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
