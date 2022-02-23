#include "AddListHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

AddListHandler::AddListHandler()
{
}

Net::Response AddListHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto json_payload = request.json_payload.object();
	auto list = m_parser.Parse(json_payload);

	if (request.uid != list.owner_id){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't create list with owner id \"" + std::to_string(list.owner_id) + "\"");
	}

	if (user_id != list.owner_id){
		return FormErrorResponse(
			NetError::Status::HTTP_BAD_REQUEST,
			"List id in uri and in json are not equal");
	}

	auto list_db = ToDBList(list);
	ListId list_id;
	try {
		list_id.id = m_facade->AddList(list_db).value();
	}
	catch (const db::SQLFailure& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}
	return FormJSONResponse(
		m_formatter.Format(list_id),
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
}

