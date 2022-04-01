#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class UpdateIncomeCategoryModel
{
public:
	UpdateIncomeCategoryModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const IncomeCategory& category);
private:
	const std::string& m_hostname{};

	IncomeCategoryJSONFormatter m_formatter{};
};
