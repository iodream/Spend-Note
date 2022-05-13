#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddPeriodicIncomeModel
{
public:
	AddPeriodicIncomeModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const PeriodicIncome& income);
	PeriodicIncomeId ParseResponse(const Net::Response& response);
	bool CheckFields(const PeriodicIncome&);
private:
	const std::string& m_hostname;

	PeriodicIncomeJSONFormatter m_formatter{};
	PeriodicIncomeIdJSONParser m_parser{};
};
