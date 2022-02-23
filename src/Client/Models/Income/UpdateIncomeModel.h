#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class UpdateIncomeModel
{
public:
	UpdateIncomeModel(const std::string& hostname) : m_hostname{hostname} {}
	bool CheckExpDate(const Income& income);
	bool CheckFields(const Income& income);

	Net::Request FormRequest(const Income& income);
private:
	const std::string& m_hostname{};

	IncomeJSONFormatter m_formatter{};
};
