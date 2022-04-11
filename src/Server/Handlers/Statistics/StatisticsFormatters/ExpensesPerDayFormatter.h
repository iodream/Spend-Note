#pragma once

#include "IStatisticsFormatter.h"
#include "../../Entities/Formatters.h"

class ExpensesPerDayFormatter : public IStatisticsFormatter
{
public:
	ExpensesPerDayFormatter(db::IDbFacade::Ptr&& facade);
	virtual ~ExpensesPerDayFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) override;
private:
	StatisticsPerDayJSONFormatter m_formatter;
};
