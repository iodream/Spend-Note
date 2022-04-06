#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetStatisticsPercentagePerCategoryModel
{
public:
	GetStatisticsPercentagePerCategoryModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const IdType& user_id, const std::string& type, const std::string& period);
	std::vector<StatisticPercentagePerCategory> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	StatisticsPercentagePerCategoryJSONParser m_parser{};
};
