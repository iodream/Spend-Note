#include <QJsonArray>

#include "GetProductsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"

GetProductsHandler::GetProductsHandler(IDbFacade::Ptr facade)
	: AuthorizedHandler(std::move(facade))
{
}

QJsonDocument GetProductsHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;

	QJsonArray products;
	for (const auto& dto_item : dto) {
		QJsonObject product;

		product["id"] = std::to_string(dto_item.first.id).c_str();
		product["list_id"] = std::to_string(dto_item.first.list_id).c_str();
		product["category_id"] = std::to_string(dto_item.first.category_id).c_str();
		product["category"] = dto_item.second.c_str();
		product["name"] = dto_item.first.name.c_str();
		product["price"] = dto_item.first.price;
		product["amount"] = dto_item.first.amount;
		product["priority"] = dto_item.first.product_priority;
		product["is_bought"] = dto_item.first.is_bought;
		product["add_date"] = dto_item.first.add_date.c_str();

		product["purchase_date"] = (dto_item.first.purchase_date)
			? dto_item.first.purchase_date->c_str() : EMPTY_C_STRING;
		product["buy_until_date"] = (dto_item.first.buy_until_date)
			? dto_item.first.buy_until_date->c_str() : EMPTY_C_STRING;

		products.append(product);
	}
	json["products"] = products;

	return QJsonDocument{json};
}

GetProductsHandler::JSONParser::DTO GetProductsHandler::JSONParser::Parse(
	const QJsonDocument& payload)
{
	DTO dto;
	auto json = payload.object();

	try {
		SafeReadId(json, "list_id", dto.list_id);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response GetProductsHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_POST) {
		auto in_dto = m_parser.Parse(request.json_payload);

		auto products = m_facade->GetProductsForList(in_dto.list_id);

		JSONFormatter::DTO out_dto;
		for (const Product& product : products) {
			auto category = m_facade->GetProductCategoryById(product.category_id);
			std::string category_name = (category) ? category->name : EMPTY_STD_STRING;
			out_dto.push_back({product, category_name});
		}

		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
