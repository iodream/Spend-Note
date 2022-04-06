#pragma once

#include "memory"
#include "QJsonArray"

#include "StatisticsFormatters/IStatisticsFormatter.h"
#include "../libdal/Types.h"

class StatisticsFormatterManager
{
public:
	StatisticsFormatterManager() {}
	~StatisticsFormatterManager() {}
	void set_formatter(IStatisticsFormatter* formatter, db::IDbFacade::Ptr&& facade);
	QJsonArray ConcreteStatisticsFormat(const db::IdType& user_id, const db::Period& period);
private:
	IStatisticsFormatter* m_formatter;
};
