#include "Utils.h"

#include "Logger/ScopedLogger.h"

StatisticPerCategory ToNetStatisticPerCategory(const db::ExpensePerCategory& db_expense)
{
	SCOPED_LOGGER;
	StatisticPerCategory statistic;
	statistic.category_id = db_expense.category_id;
	statistic.amount = db_expense.amount;
	return statistic;
}

StatisticPercentagePerCategory ToNetStatisticPercentagePerCategory(const db::ExpensePercentagePerCategory& db_expense)
{
	SCOPED_LOGGER;
	StatisticPercentagePerCategory statistic;
	statistic.category_id = db_expense.category_id;
	statistic.percentage = db_expense.percentage;
	return statistic;
}

StatisticPerDay ToNetStatisticPerDay(const db::ExpensePerDay& db_expense)
{
	SCOPED_LOGGER;
	StatisticPerDay statistic;
	statistic.day = db_expense.day;
	statistic.amount = db_expense.amount;
	return statistic;
}

StatisticPerCategory ToNetStatisticPerCategory(const db::IncomePerCategory& db_income)
{
	SCOPED_LOGGER;
	StatisticPerCategory statistic;
	statistic.category_id = db_income.category_id;
	statistic.amount = db_income.amount;
	return statistic;
}

StatisticPercentagePerCategory ToNetStatisticPercentagePerCategory(const db::IncomePercentagePerCategory& db_income)
{
	SCOPED_LOGGER;
	StatisticPercentagePerCategory statistic;
	statistic.category_id = db_income.category_id;
	statistic.percentage = db_income.percentage;
	return statistic;
}

StatisticPerDay ToNetStatisticPerDay(const db::IncomePerDay& db_income)
{
	SCOPED_LOGGER;
	StatisticPerDay statistic;
	statistic.day = db_income.day;
	statistic.amount = db_income.amount;
	return statistic;
}
