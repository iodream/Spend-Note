#include "IncomesPercentagePerCategoryFormatter.h"
#include "Utils.h"

IncomesPercentagePerCategoryFormatter::IncomesPercentagePerCategoryFormatter(db::IDbFacade::Ptr&& facade)
	: IStatisticsFormatter(std::move(facade)) {

}

QJsonArray IncomesPercentagePerCategoryFormatter::StatisticsFormat(const db::IdType& user_id, const db::Period& period) {
	auto db_incomes = m_facade->IncomesPercentagePerCategory(user_id, period);
	std::vector<StatisticPercentagePerCategory> incomes;
	for (auto db_income : db_incomes) {
		auto income = ToNetStatisticPercentagePerCategory(db_income);
		incomes.push_back(income);
	}
	return m_formatter.Format(incomes);
}
