#include <QJsonArray>

#include "RemoveListHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

RemoveListHandler::RemoveListHandler()
{
}

Net::Response RemoveListHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto list_id = std::get<long long>(m_params.Get(Params::LIST_ID));

	if (!m_facade->GetListById(list_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}

	if (!m_facade->CanUserEditList(request.uid, list_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Remove list with id \"" + std::to_string(list_id) + "\" is forbidden");
	}

	m_facade->RemoveList(list_id);
	return FormEmptyResponse();
}
