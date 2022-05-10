#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/PeriodicIncome/PeriodicIncomeId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class RemovePeriodicIncomeModel
{
public:
	RemovePeriodicIncomeModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const PeriodicIncomeId& income_id);
private:
	const std::string& m_hostname{};

};

