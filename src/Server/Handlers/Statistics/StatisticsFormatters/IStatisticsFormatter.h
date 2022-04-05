#pragma once

#include <string>
#include <QJsonObject>

#include "../../../libdal/Facade/IDbFacade.h"
#include "../../../libdal/Types.h"

class IStatisticsFormatter
{
public:
	IStatisticsFormatter(db::IDbFacade::Ptr&& facade);
	virtual ~IStatisticsFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) = 0;
protected:
	db::IDbFacade::Ptr m_facade;
};
