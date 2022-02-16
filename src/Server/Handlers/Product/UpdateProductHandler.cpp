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
	auto product_id = std::get<long long>(m_params.Get(Params::PRODUCT_ID));
	auto json_payload = request.json_payload.object();
	auto product = m_parser.Parse(json_payload);

	if (product_id != product.id){
		return FormErrorResponse(
			NetError::Status::HTTP_BAD_REQUEST,
			"Product id in uri and in json are not equal");
	}

	if (!m_facade->CanUserEditProduct(request.uid, product_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Update product with id " + std::to_string(product_id) + " is forbidden");
	}

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
