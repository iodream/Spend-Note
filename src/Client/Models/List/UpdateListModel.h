#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class UpdateListModel
{
public:
	UpdateListModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const List& list);
private:
	std::string m_hostname{};

	ListJSONFormatter m_formatter{};
};
