#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class UpdatePeriodicIncomeModel
{
public:
	UpdatePeriodicIncomeModel(const std::string& hostname) : m_hostname{hostname} {}
	bool CheckFields(const PeriodicIncome& income);

	Net::Request FormRequest(const PeriodicIncome& income);
private:
	const std::string& m_hostname{};

	PeriodicIncomeJSONFormatter m_formatter{};
};
