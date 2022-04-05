#pragma once

#include <vector>

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetProductCategoriesModel
{
public:
	GetProductCategoriesModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const IdType& user_id);
	std::vector<ProductCategory> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	ProductCategoriesJSONParser m_parser{};
};
