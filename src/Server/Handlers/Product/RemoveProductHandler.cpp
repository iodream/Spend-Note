#include <QJsonArray>

#include "RemoveProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

RemoveProductHandler::RemoveProductHandler()
{
}

Net::Response RemoveProductHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);
	auto product_id = std::get<long long>(m_params.Get(Params::PRODUCT_ID));

	if (m_facade->RemoveProduct(product_id)) {
		return FormEmptyResponse();
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}
}
