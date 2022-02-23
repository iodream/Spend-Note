#include <QJsonArray>

#include "GetExpensesPercentagePerCategoryHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "../libdal/Exceptions/NonexistentResource.h"
#include "Utils.h"


GetExpensesPercentagePerCategoryHandler::GetExpensesPercentagePerCategoryHandler()
{
}

Net::Response GetExpensesPercentagePerCategoryHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	if (request.uid != user_id){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't get expenses for user with id \"" + std::to_string(user_id) + "\"");
	}

	std::vector<db::ExpensePercentagePerCategory> db_expenses;

	try {
		db_expenses = m_facade->ExpensesPercentagePerCategory(user_id);
	}
	catch (const db::NonexistentResource& ex) {
		return FormErrorResponse(NetError::Status::HTTP_NOT_FOUND, ex.what());
	}

	std::vector<ExpensePercentagePerCategory> expenses;
	for (auto db_expense : db_expenses) {
		auto expense = ToNetExpensePercentagePerCategory(db_expense);
		expenses.push_back(expense);
	}

	return FormJSONResponse(m_formatter.Format(expenses));
}
