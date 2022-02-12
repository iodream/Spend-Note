#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetBalanceModel
{
public:
	GetBalanceModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(IdType user_id);
	Balance ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	BalanceJSONParser m_parser{};
};
