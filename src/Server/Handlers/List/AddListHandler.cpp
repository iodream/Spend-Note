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

db::List AddListHandler::ToDBList(const List& list)
{
	db::List db_list;
	db_list.id = list.id;
	db_list.name = list.name;
	db_list.owner_id = list.owner_id;
	db_list.state_id = list.state.id;
	return db_list;
}

Net::Response AddListHandler::AuthHandle(const Net::Request& request)
{
	auto json_payload = request.json_payload.object();
	auto list = m_parser.Parse(json_payload);
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

