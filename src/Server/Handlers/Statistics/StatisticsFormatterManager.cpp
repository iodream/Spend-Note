#include "StatisticsFormatterManager.h"

void StatisticsFormatterManager::set_formatter(IStatisticsFormatter* formatter, db::IDbFacade::Ptr&& facade) {
	m_formatter = formatter;
	m_formatter->set_facade(std::move(facade));
}

QJsonArray StatisticsFormatterManager::ConcreteStatisticsFormat(const db::IdType &user_id, const db::Period &period) {
	return m_formatter->StatisticsFormat(user_id, period);
}
