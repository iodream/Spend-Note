#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Tools/Formatters/Product/ProductJSONFormatter.h"
#include "Net/Tools/Parsers/Product/ProductIdJSONParser.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddProductModel
{
public:
	AddProductModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const Product<QString>& product);
	ProductId ParseResponse(const Net::Response& response);
private:
	const std::string& m_hostname;

	ProductJSONFormatter<Product<QString>> m_formatter{};
	ProductIdJSONParser m_parser{};
};
