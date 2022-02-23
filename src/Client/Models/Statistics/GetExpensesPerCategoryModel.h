#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class GetExpensesPerCategoryModel
{
public:
	GetExpensesPerCategoryModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(IdType user_id);
	std::vector<ExpensePerCategory> ParseResponse(const Net::Response& response);

private:
	const std::string& m_hostname;

	ExpensesPerCategoryJSONParser m_parser{};
};
