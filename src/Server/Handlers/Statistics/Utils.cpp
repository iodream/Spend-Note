#include "Utils.h"

#include "Logger/ScopedLogger.h"

StatisticPerCategory ToNetStatisticPerCategory(const db::ExpensePerCategory& db_expense)
{
	SCOPED_LOGGER;
	StatisticPerCategory expense;
	expense.category_id = db_expense.category_id;
	expense.amount = db_expense.amount;
	return expense;
}

StatisticPercentagePerCategory ToNetStatisticPercentagePerCategory(const db::ExpensePercentagePerCategory& db_expense)
{
	SCOPED_LOGGER;
	StatisticPercentagePerCategory expense;
	expense.category_id = db_expense.category_id;
	expense.percentage = db_expense.percentage;
	return expense;
}

StatisticPerDay ToNetStatisticPerDay(const db::ExpensePerDay& db_expense)
{
	SCOPED_LOGGER;
	StatisticPerDay expense;
	expense.day = db_expense.day;
	expense.amount = db_expense.amount;
	return expense;
}
