#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Client/Entities/Formatters.h"
#include "Client/Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddIncomeCategoryModel
{
public:
	AddIncomeCategoryModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const IdType& user_id, const IncomeCategory& product_category);
	IncomeCategoryId ParseResponse(const Net::Response& response);
private:
	const std::string& m_hostname;

	IncomeCategoryJSONFormatter m_formatter{};
	IncomeCategoryIdJSONParser m_parser{};
};
