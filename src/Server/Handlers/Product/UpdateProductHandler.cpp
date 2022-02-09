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

db::Product UpdateProductHandler::ToDBProduct(const Product& product)
{
	SCOPED_LOGGER;
	db::Product db_product;
	db_product.id = product.id;
	db_product.list_id = product.list_id;
	db_product.category_id = product.category.id;
	db_product.name = product.name;
	db_product.price = product.price;
	db_product.amount = product.amount;
	db_product.product_priority = product.priority;
	db_product.is_bought = product.is_bought;
	db_product.add_date = product.add_date;
	db_product.purchase_date = product.purchase_date;
	db_product.buy_until_date = product.buy_until_date;
	return db_product;
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
