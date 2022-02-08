#include "UpdateListHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

UpdateListHandler::UpdateListHandler()
{
}

db::List UpdateListHandler::ToDBList(const List& list)
{
	db::List db_list;
	db_list.id = list.id;
	db_list.name = list.name;
	db_list.owner_id = list.owner_id;
	db_list.state_id = list.state.id;
	return db_list;
}

Net::Response UpdateListHandler::AuthHandle(const Net::Request& request)
{
	auto json_payload = request.json_payload.object();
	auto list = m_parser.Parse(json_payload);
	auto list_db = ToDBList(list);

	if (m_facade->UpdateList(list_db)) {
		return FormEmptyResponse();
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}
}
