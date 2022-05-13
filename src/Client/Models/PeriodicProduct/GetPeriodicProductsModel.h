#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetPeriodicProductsModel
{
public:
	GetPeriodicProductsModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(IdType list_id);
	std::vector<PeriodicProduct> ParseResponse(const Net::Response response);
private:
	const std::string& m_hostname{};

	PeriodicProductsJSONParser m_parser{};
};

