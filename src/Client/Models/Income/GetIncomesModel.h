#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetIncomesModel
{
public:
	GetIncomesModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(IdType user_id);
	std::vector<Income> ParseResponse(const Net::Response response);
private:
	std::string m_hostname{};

	IncomesJSONParser m_parser{};
};

