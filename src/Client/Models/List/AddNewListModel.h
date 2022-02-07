#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/List/ListId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddNewListsModel
{
public:
	AddNewListsModel(const std::string& hostname) : m_hostname{hostname} {}
	Net::Request FormRequest(IdType user_id);
	ListId ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;
};

