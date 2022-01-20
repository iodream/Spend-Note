#include "QJsonObject"
#include "QJsonArray"

#include "GetListsHandler.h"
#include "Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"

QJsonDocument GetListsHandler::JSONFormatter::Format(const std::vector<DTO>& dtoVector)
{
	QJsonArray jsonarray;
	QJsonObject finaljson;
	for (int i = 0; i < int(dtoVector.size()); i++)
	{
		QJsonObject json;
		json["id"] = dtoVector[i].id;
		//json["ownerId"] = dtoVector[i].ownerId;
		//json["stateId"] = dtoVector[i].stateId;
		json["name"] = QString::fromStdString(dtoVector[i].name);
		jsonarray.append(json);
	}
	finaljson["lists"] = jsonarray;
	return QJsonDocument(finaljson);
}

Net::Response GetListsHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_GET) {
		std::vector<JSONFormatter::DTO> vector;
		// do something to get vector
		return FormJSONResponse(m_formatter.Format(vector));
	}
	return FormErrorResponse(
		Net::NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
