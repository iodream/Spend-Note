#include "StatisticsFormatterManager.h"

void StatisticsFormatterManager::set_formatter(IStatisticsFormatter* formatter) {
	m_formatter = formatter;
}

QJsonArray StatisticsFormatterManager::ConcreteStatisticsFormat(const db::IdType &user_id, const db::Period &period) {
	return m_formatter->StatisticsFormat(user_id, period);
}
