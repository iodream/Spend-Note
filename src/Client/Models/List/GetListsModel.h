#pragma once

#include <vector>

#include <QJsonDocument>
#include <QJsonObject>

#include "DTO/Login.h"
#include "Net/Constants.h"
#include "Net/Message.h"

#include "DTO/List.h"

class GetListsModel
{
public:
	GetListsModel(const std::string& hostname) : m_hostname{hostname} {}

	class JSONParser
	{
	public:
		void Parse(QJsonObject json, std::vector<List>& lists);
	};

	Net::Request FormRequest();
	std::vector<List> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	JSONParser m_parser{};
};

