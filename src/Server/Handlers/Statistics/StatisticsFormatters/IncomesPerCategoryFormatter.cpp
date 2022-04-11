#include "IncomesPerCategoryFormatter.h"
#include "Utils.h"

IncomesPerCategoryFormatter::IncomesPerCategoryFormatter(db::IDbFacade::Ptr&& facade)
	: IStatisticsFormatter(std::move(facade)) {

}

QJsonArray IncomesPerCategoryFormatter::StatisticsFormat(const db::IdType& user_id, const db::Period& period) {
	auto db_incomes = m_facade->IncomesPerCategory(user_id, period);
	std::vector<StatisticPerCategory> incomes;
	for (auto db_income : db_incomes) {
		auto income = ToNetStatisticPerCategory(db_income);
		incomes.push_back(income);
	}
	return m_formatter.Format(incomes);
}
