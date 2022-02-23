#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetExpensesPercentagePerCategoryModel
{
public:
	GetExpensesPercentagePerCategoryModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(IdType user_id);
	std::vector<ExpensePercentagePerCategory> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	ExpensesPercentagePerCategoryJSONParser m_parser{};
};
