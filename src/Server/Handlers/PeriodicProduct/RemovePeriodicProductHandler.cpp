#include <QJsonArray>

#include "RemovePeriodicProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

RemovePeriodicProductHandler::RemoveProductHandler()
{
}

Net::Response RemovePeriodicProductHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto product_id = std::get<long long>(m_params.Get(Params::PRODUCT_ID));

	if (!m_facade->GetPeriodicProductById(product_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}

	if (!m_facade->CanUserEditPeriodicProduct(request.uid, product_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Remove product with id \"" + std::to_string(product_id) + "\" is forbidden");
	}

	m_facade->RemovePeriodicProduct(product_id);
	return FormEmptyResponse();
}
