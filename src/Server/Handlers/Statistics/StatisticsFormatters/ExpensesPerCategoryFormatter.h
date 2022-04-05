#pragma once

#include "IStatisticsFormatter.h"
#include "../../Entities/Formatters.h"

class ExpensesPerCategoryFormatter : public IStatisticsFormatter
{
public:
	ExpensesPerCategoryFormatter(db::IDbFacade::Ptr&& facade);
	virtual ~ExpensesPerCategoryFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) override;
private:
	StatisticsPerCategoryJSONFormatter m_formatter;
};
