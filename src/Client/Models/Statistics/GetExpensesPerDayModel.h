#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetExpensesPerDayModel
{
public:
	GetExpensesPerDayModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(IdType user_id);
	std::vector<StatisticPerDay> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	StatisticsPerDayJSONParser m_parser{};
};
