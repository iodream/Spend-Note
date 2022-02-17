#pragma once

#include <vector>

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetListStatesModel
{
public:
	GetListStatesModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest();
	std::vector<ListState> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	ListStatesJSONParser m_parser{};
};
