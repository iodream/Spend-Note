#pragma once

#include <vector>

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetListsModel
{
public:
	GetListsModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(IdType user_id);
	std::vector<List> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	ListsJSONParser m_parser{};
};

