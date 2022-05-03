#include "GetRecommendationProductModel.h"

Net::Request GetRecommendationProductModel::FormRequest(IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/users/" + std::to_string(user_id) + "/recommendation";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_EMPTY;
	return request;
}

Product GetRecommendationProductModel::ParseResponse(const Net::Response response)
{
	Product product;

	product = m_parser.Parse(response.json_payload.object());

	return product;
}
