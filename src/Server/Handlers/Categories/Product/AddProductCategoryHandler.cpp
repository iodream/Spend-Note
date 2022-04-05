#include <QJsonArray>

#include "AddProductCategoryHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

AddProductCategoryHandler::AddProductCategoryHandler()
{
}

Net::Response AddProductCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto json_payload = request.json_payload.object();
	auto product_category = m_parser.Parse(json_payload);
	auto product_category_db = ToDBProductCategory(product_category, user_id);

	ProductCategoryId product_category_id;
	try {
		product_category_id.id = m_facade->AddProductCategory(product_category_db).value();
	}
	catch (const db::SQLFailure& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}
	return FormJSONResponse(
		m_formatter.Format(product_category_id),
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
}
