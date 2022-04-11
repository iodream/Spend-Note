#pragma once

#include "IStatisticsFormatter.h"
#include "../../Entities/Formatters.h"

class ExpensesPercentagePerCategoryFormatter : public IStatisticsFormatter
{
public:
	ExpensesPercentagePerCategoryFormatter(db::IDbFacade::Ptr&& facade);
	virtual ~ExpensesPercentagePerCategoryFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) override;
private:
	StatisticsPercentagePerCategoryJSONFormatter m_formatter;
};
