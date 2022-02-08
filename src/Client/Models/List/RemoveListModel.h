#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/List/ListId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class RemoveListModel
{
public:
	RemoveListModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const ListId& list_id);
private:
	std::string m_hostname{};
};
