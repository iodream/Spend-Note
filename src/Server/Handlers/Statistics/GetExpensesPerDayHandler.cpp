#include <QJsonArray>

#include "GetExpensesPerDayHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "../libdal/Exceptions/NonexistentResource.h"
#include "Utils.h"


GetExpensesPerDayHandler::GetExpensesPerDayHandler()
{
}

Net::Response GetExpensesPerDayHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	std::vector<db::ExpensePerDay> db_expenses;

	try {
		db_expenses = m_facade->ExpensesDynamics(user_id);
	}
	catch (const db::NonexistentResource& ex) {
		return FormErrorResponse(NetError::Status::HTTP_NOT_FOUND, ex.what());
	}

	std::vector<ExpensePerDay> expenses;
	for (const db::ExpensePerDay& db_expense : db_expenses) {
		auto expense = ToNetExpensePerDay(db_expense);
		expenses.push_back(expense);
	}

	return FormJSONResponse(m_formatter.Format(expenses));
}
