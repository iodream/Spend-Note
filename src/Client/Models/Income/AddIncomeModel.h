#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddIncomeModel
{
public:
	AddIncomeModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const Income& income);
	IncomeId ParseResponse(const Net::Response& response);
private:
	const std::string& m_hostname;

	IncomeJSONFormatter m_formatter{};
	IncomeIdJSONParser m_parser{};
};
