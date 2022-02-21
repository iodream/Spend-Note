#include "Utils.h"

#include "Logger/ScopedLogger.h"

ExpensePerCategory ToNetExpensePerCategory(const db::ExpensePerCategory& db_expense)
{
	SCOPED_LOGGER;
	ExpensePerCategory expense;
	expense.category_id = db_expense.category_id;
	expense.amount = db_expense.amount;
	return expense;
}
