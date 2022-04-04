#include "UpdateProductCategoryHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

UpdateProductCategoryHandler::UpdateProductCategoryHandler()
{
}

Net::Response UpdateProductCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto product_category_id = std::get<long long>(m_params.Get(Params::PRODUCT_CATEGORY_ID));

	if (!m_facade->GetProductCategoryById(product_category_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}

	auto json_payload = request.json_payload.object();
	auto product_category = m_parser.Parse(json_payload);

	if (!m_facade->CanUserEditProductCategory(request.uid, product_category_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Update product category with id \"" + std::to_string(product_category_id) + "\" is forbidden");
	}

	auto product_category_db = ToDBProductCategory(product_category, request.uid);

	m_facade->UpdateProductCategory(product_category_db);
	return FormEmptyResponse();
}
