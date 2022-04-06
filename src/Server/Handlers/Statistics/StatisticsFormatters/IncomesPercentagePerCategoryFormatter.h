#pragma once

#include "IStatisticsFormatter.h"
#include "../../Entities/Formatters.h"

class IncomesPercentagePerCategoryFormatter : public IStatisticsFormatter
{
public:
	IncomesPercentagePerCategoryFormatter();
	virtual ~IncomesPercentagePerCategoryFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) override;
private:
	StatisticsPercentagePerCategoryJSONFormatter m_formatter;
};
