#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetStatisticsPerDayModel
{
public:
	GetStatisticsPerDayModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const IdType& user_id, const std::string& type, const std::string& period);
	std::vector<StatisticPerDay> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	StatisticsPerDayJSONParser m_parser{};
};
