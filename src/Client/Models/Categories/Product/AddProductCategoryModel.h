#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddProductCategoryModel
{
public:
	AddProductCategoryModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const IdType& user_id, const ProductCategory& product_category);
	ProductCategoryId ParseResponse(const Net::Response& response);
	static bool CheckFields(ProductCategory& product_category);

private:
	const std::string& m_hostname;

	ProductCategoryJSONFormatter m_formatter{};
	ProductCategoryIdJSONParser m_parser{};
};
