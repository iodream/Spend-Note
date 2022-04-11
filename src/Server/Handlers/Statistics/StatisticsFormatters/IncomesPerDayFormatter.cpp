#include "IncomesPerDayFormatter.h"
#include "Utils.h"

IncomesPerDayFormatter::IncomesPerDayFormatter(db::IDbFacade::Ptr&& facade)
	: IStatisticsFormatter(std::move(facade)) {

}

QJsonArray IncomesPerDayFormatter::StatisticsFormat(const db::IdType& user_id, const db::Period& period) {
	auto db_incomes = m_facade->IncomesDynamics(user_id, period);
	std::vector<StatisticPerDay> incomes;
	for (auto db_income : db_incomes) {
		auto income = ToNetStatisticPerDay(db_income);
		incomes.push_back(income);
	}
	return m_formatter.Format(incomes);
}
