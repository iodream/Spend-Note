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

Net::Response UpdateListHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto list_id = std::get<long long>(m_params.Get(Params::LIST_ID));
	auto json_payload = request.json_payload.object();
	auto list = m_parser.Parse(json_payload);

	if (list_id != list.id){
		return FormErrorResponse(
			NetError::Status::HTTP_BAD_REQUEST,
			"List id in uri and in json are not equal");
	}

	if (!m_facade->CanUserEditList(request.uid, list_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Update list with id " + std::to_string(list_id) + " is forbidden");
	}

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
