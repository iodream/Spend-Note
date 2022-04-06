#include "ExpensesPerDayFormatter.h"
#include "Utils.h"

ExpensesPerDayFormatter::ExpensesPerDayFormatter()
{

}

QJsonArray ExpensesPerDayFormatter::StatisticsFormat(const db::IdType& user_id, const db::Period& period) {
	auto db_expenses = m_facade->ExpensesDynamics(user_id, period);
	std::vector<StatisticPerDay> expenses;
	for (auto db_expense : db_expenses) {
		auto expense = ToNetStatisticPerDay(db_expense);
		expenses.push_back(expense);
	}
	return m_formatter.Format(expenses);
}
