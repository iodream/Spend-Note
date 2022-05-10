#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddPeriodicProductModel
{
public:
	AddPeriodicProductModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const PeriodicProduct& product);
	PeriodicProductId ParseResponse(const Net::Response& response);
	static bool CheckFields(PeriodicProduct& product);

private:
	const std::string& m_hostname;

	PeriodicProductJSONFormatter m_formatter{};
	PeriodicProductIdJSONParser m_parser{};
};
