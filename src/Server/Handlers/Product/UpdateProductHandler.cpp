#include "UpdateProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

UpdateProductHandler::UpdateProductHandler()
{
}

Net::Response UpdateProductHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto json_payload = request.json_payload.object();
	auto product = m_parser.Parse(json_payload);
	auto product_db = ToDBProduct(product);

	if (m_facade->UpdateProduct(product_db)) {
		return FormEmptyResponse();
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}
}
