#pragma once

#include <vector>

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetIncomeCategoriesModel
{
public:
	GetIncomeCategoriesModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest();
	std::vector<IncomeCategory> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	IncomeCategoriesJSONParser m_parser{};
};
