#pragma once

#include "IStatisticsFormatter.h"
#include "../../Entities/Formatters.h"

class IncomesPerCategoryFormatter : public IStatisticsFormatter
{
public:
	IncomesPerCategoryFormatter(db::IDbFacade::Ptr&& facade);
	virtual ~IncomesPerCategoryFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) override;
private:
	StatisticsPerCategoryJSONFormatter m_formatter;
};
