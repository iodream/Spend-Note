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
