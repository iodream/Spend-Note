#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetRecommendationProductModel
{
public:
	GetRecommendationProductModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(IdType user_id);
	Product ParseResponse(const Net::Response response);
private:
	const std::string& m_hostname{};

	ProductJSONParser m_parser{};
};
