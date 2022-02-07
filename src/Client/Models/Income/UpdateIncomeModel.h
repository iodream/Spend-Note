#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetIncomesModel
{
public:
	GetIncomesModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const Income& income);
private:
	std::string m_hostname{};

	IncomeJSONFormatter m_formatter{};
};
