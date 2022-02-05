#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Tools/Parsers/Income/IncomesJSONParser.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetIncomesModel
{
public:
	GetIncomesModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(/**/);
	std::vector<Income<QString>> ParseResponse(const Net::Response response);
private:
	std::string m_hostname{};

	IncomeArrayJSONParser<Income<QString>> m_parser{};
};

