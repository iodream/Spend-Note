#pragma once

#include <vector>

#include <QJsonDocument>
#include <QJsonArray>

#include "Net/Constants.h"
#include "Net/Message.h"

#include "Client/Common.h"

#include "Client/Entities/Entities.h"

class GetListsModel
{
public:
	GetListsModel(const std::string& hostname) : m_hostname{hostname} {}
	Net::Request FormRequest(IdType user_id);
	std::vector<List> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;
};

