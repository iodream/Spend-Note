#include <QJsonArray>

#include "AddProductHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"

AddProductHandler::AddProductHandler()
{
}
Product AddProductHandler::JSONParser::Parse(
	const QJsonDocument& payload)
{
	auto json = payload.object();
	return ParseProduct(json);
}

QJsonDocument AddProductHandler::JSONFormatter::Format(const Product& dto)
{
	QJsonObject json;

	json["id"] = std::to_string(dto.id).c_str();

	return QJsonDocument{json};
}

Net::Response AddProductHandler::AuthHandle(const Net::Request& request)
{
	auto product = m_parser.Parse(request.json_payload);
	auto list_id = std::get<long long>(m_params.Get(Params::LIST_ID));
	product.list_id = list_id;

	JSONFormatter::Product out_dto;

	try {
		out_dto.id = m_facade->AddProduct(product).value();
	}
	catch (const SQLFailure& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}

	return FormJSONResponse(
		m_formatter.Format(out_dto),
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CREATED);
}
