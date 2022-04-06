#pragma once

#include "IStatisticsFormatter.h"
#include "../../Entities/Formatters.h"

class IncomesPerDayFormatter : public IStatisticsFormatter
{
public:
	IncomesPerDayFormatter();
	virtual ~IncomesPerDayFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) override;
private:
	StatisticsPerDayJSONFormatter m_formatter;
};
