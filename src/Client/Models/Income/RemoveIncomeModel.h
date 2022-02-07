#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/Income/IncomeId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class RemoveIncomeModel
{
public:
	RemoveIncomeModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const IncomeId& income_id);
private:
	const std::string& m_hostname{};

};

