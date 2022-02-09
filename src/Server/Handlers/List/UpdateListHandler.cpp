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
