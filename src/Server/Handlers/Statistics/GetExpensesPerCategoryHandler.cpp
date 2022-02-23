#include <QJsonArray>

#include "GetExpensesPerCategoryHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "../libdal/Exceptions/NonexistentResource.h"
#include "Utils.h"


GetExpensesPerCategoryHandler::GetExpensesPerCategoryHandler()
{
}

Net::Response GetExpensesPerCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	std::vector<db::ExpensePerCategory> db_expenses;

	try {
		db_expenses = m_facade->ExpensesPerCategory(user_id);
	}
	catch (const db::NonexistentResource& ex) {
		return FormErrorResponse(NetError::Status::HTTP_NOT_FOUND, ex.what());
	}

	std::vector<ExpensePerCategory> expenses;
	for (auto db_expense : db_expenses) {
		auto expense = ToNetExpensePerCategory(db_expense);
		expenses.push_back(expense);
	}

	return FormJSONResponse(m_formatter.Format(expenses));
}
