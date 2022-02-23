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
	auto list_id = std::get<long long>(m_params.Get(Params::LIST_ID));
	auto json_payload = request.json_payload.object();
	auto product = m_parser.Parse(json_payload);
	auto product_db = ToDBProduct(product);

	if (list_id != product.list_id){
		return FormErrorResponse(
			NetError::Status::HTTP_BAD_REQUEST,
			"List id in uri and in json are not equal");
	}

	if (m_facade->CanUserEditList(request.uid, product.list_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't create product with list id \"" + std::to_string(product.list_id) + "\"");;
	}

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
