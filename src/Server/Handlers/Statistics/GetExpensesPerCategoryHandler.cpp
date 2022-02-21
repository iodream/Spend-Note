#include <QJsonArray>

#include "GetExpensesPerCategoryHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "Utils.h"


GetExpensesPerCategoryHandler::GetExpensesPerCategoryHandler()
{
}

Net::Response GetExpensesPerCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	auto db_expenses = m_facade->ExpensesPerCategory(user_id);
	std::vector<ExpensePerCategory> expenses;

	for (auto db_expense : db_expenses) {
		auto expense = ToNetExpensePerCategory(db_expense);
		expenses.push_back(expense);
	}

	return FormJSONResponse(m_formatter.Format(expenses));
}
