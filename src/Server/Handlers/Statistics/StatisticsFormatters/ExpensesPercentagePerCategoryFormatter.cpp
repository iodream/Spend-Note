#include "ExpensesPercentagePerCategoryFormatter.h"
#include "Utils.h"

ExpensesPercentagePerCategoryFormatter::ExpensesPercentagePerCategoryFormatter(db::IDbFacade::Ptr&& facade)
	: IStatisticsFormatter(std::move(facade)) {

}

QJsonArray ExpensesPercentagePerCategoryFormatter::StatisticsFormat(const db::IdType& user_id, const db::Period& period) {
	auto db_expenses = m_facade->ExpensesPercentagePerCategory(user_id, period);
	std::vector<StatisticPercentagePerCategory> expenses;
	for (auto db_expense : db_expenses) {
		auto expense = ToNetStatisticPercentagePerCategory(db_expense);
		expenses.push_back(expense);
	}
	return m_formatter.Format(expenses);
}
