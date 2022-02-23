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

ExpensePercentagePerCategory ToNetExpensePercentagePerCategory(const db::ExpensePercentagePerCategory& db_expense)
{
	SCOPED_LOGGER;
	ExpensePercentagePerCategory expense;
	expense.category_id = db_expense.category_id;
	expense.percentage = db_expense.percentage;
	return expense;
}

ExpensePerDay ToNetExpensePerDay(const db::ExpensePerDay& db_expense)
{
	SCOPED_LOGGER;
	ExpensePerDay expense;
	expense.day = db_expense.day;
	expense.amount = db_expense.amount;
	return expense;
}
