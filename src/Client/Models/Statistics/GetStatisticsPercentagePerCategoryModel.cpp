#include "GetStatisticsPercentagePerCategoryModel.h"

namespace {
const std::string FORMAT = "percentage-per-category";
}

Net::Request GetStatisticsPercentagePerCategoryModel::FormRequest(const IdType& user_id, const std::string& type, const std::string& period)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/statistics?"
			+ type + "&" + period + "&" + FORMAT;
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

std::vector<StatisticPercentagePerCategory> GetStatisticsPercentagePerCategoryModel::ParseResponse(const Net::Response& response)
{
	std::vector<StatisticPercentagePerCategory> statistics;

	statistics = m_parser.Parse(response.json_payload.array());

	return statistics;
}
