#include <QJsonArray>

#include "GetRecommendationProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "Utils.h"
#include "../libdal/Exceptions/NonexistentResource.h"

GetRecommendationProductHandler::GetRecommendationProductHandler()
{
}

Net::Response GetRecommendationProductHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	if (request.uid != user_id) {
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't get recommendation product for user with id \"" + std::to_string(user_id) + "\"");
	}

	db::Product db_product;
	try
	{
		db_product = m_facade->GetRecommendation(user_id);
	}
	catch (const db::NonexistentResource& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"User with id = \"" + std::to_string(user_id) + "\" not found");
	}

	auto category = m_facade->GetProductCategoryById(db_product.category_id);
	if (!category.has_value()) {
			throw InternalError(std::string("No product category with id:") + std::to_string(db_product.category_id));
	}
	auto product = ToNetProduct(db_product, category.value());

	return FormJSONResponse(m_formatter.Format(product));
}
