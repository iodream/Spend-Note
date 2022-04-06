#include <QJsonArray>

#include "RemoveProductCategoryHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

RemoveProductCategoryHandler::RemoveProductCategoryHandler()
{
}

Net::Response RemoveProductCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto product_category_id = std::get<long long>(m_params.Get(Params::PRODUCT_CATEGORY_ID));

	if (!m_facade->GetProductCategoryById(product_category_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"Resource not found");
	}

	if (!m_facade->CanUserEditProductCategory(request.uid, product_category_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Remove product category with id \"" + std::to_string(product_category_id) + "\" is forbidden");
	}

	try {
		m_facade->RemoveProductCategory(product_category_id);
	}  catch (const db::DatabaseFailure& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"Unable to delete category");
	}
	return FormEmptyResponse();
}
