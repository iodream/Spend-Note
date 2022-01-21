#include <memory>
#include <optional>

#include "QJsonObject"
#include "QJsonArray"

#include "GetListsHandler.h"
#include "Common.h"
#include "Net/Parsing.h"
#include "../libdal/Facade/DbFacade.h"
#include "../libdal/DTOs/List.h"
#include "../libdal/DTOs/ListState.h"
#include "Server/Error.h"
#include "Server/Utils.h"

GetListsHandler::GetListsHandler()
	: m_facade(std::make_unique<DbFacade>(DB_CONN_STRING))
{

}

QJsonDocument GetListsHandler::Format(const std::optional<std::vector<List>>& vector)
{
	QJsonObject finaljson;
	if (vector.has_value())
	{
		std::vector<List> lists = vector.value();
		QJsonArray jsonarray;
		for (int i = 0; i < int(lists.size()); i++)
		{
			QJsonObject json;
			json["id"] = lists[i].list_id;
			json["ownerId"] = lists[i].owner_id;
			json["name"] = QString::fromStdString(lists[i].name);
			auto list_state = m_facade->GetListStateById(lists[i].state_id);
			if (list_state.has_value())
			{
				json["state"] = QString::fromStdString(list_state.value().name);
			}
			jsonarray.append(json);
		}
		finaljson["lists"] = jsonarray;
	}
	return QJsonDocument(finaljson);
}

Net::Response GetListsHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_GET) {
		auto lists = m_facade->GetAllLists(request.uid);
		return FormJSONResponse(Format(lists));
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
