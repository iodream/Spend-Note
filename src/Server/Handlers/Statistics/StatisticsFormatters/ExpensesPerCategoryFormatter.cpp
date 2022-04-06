#include "ExpensesPerCategoryFormatter.h"
#include "Utils.h"

ExpensesPerCategoryFormatter::ExpensesPerCategoryFormatter ()
{

}

QJsonArray ExpensesPerCategoryFormatter::StatisticsFormat(const db::IdType& user_id, const db::Period& period) {
	auto db_expenses = m_facade->ExpensesPerCategory(user_id, period);
	std::vector<StatisticPerCategory> expenses;
	for (auto db_expense : db_expenses) {
		auto expense = ToNetStatisticPerCategory(db_expense);
		expenses.push_back(expense);
	}
	return m_formatter.Format(expenses);
}
