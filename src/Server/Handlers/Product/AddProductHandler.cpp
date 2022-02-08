#include <QJsonArray>

#include "AddProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

AddProductHandler::AddProductHandler()
{
}

db::Product AddProductHandler::ToDBProduct(const Product& product)
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
	db_product.add_date = product.add_date;
	db_product.purchase_date = product.purchase_date;
	db_product.buy_until_date = product.buy_until_date;

	return db_product;
}

Net::Response AddProductHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto json_payload = request.json_payload.object();
	auto product = m_parser.Parse(json_payload);
	auto product_db = ToDBProduct(product);
	ProductId product_id;
	try {
		product_id.id = m_facade->AddProduct(product_db).value();
	}
	catch (const db::SQLFailure& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}
	return FormJSONResponse(
		m_formatter.Format(product_id),
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
}
