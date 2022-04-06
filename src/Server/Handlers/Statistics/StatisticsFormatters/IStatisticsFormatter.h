#pragma once

#include <string>
#include <QJsonObject>

#include "../../../libdal/Facade/IDbFacade.h"
#include "../../../libdal/Types.h"

class IStatisticsFormatter
{
public:
	IStatisticsFormatter() {}
	virtual ~IStatisticsFormatter() {}
	virtual QJsonArray StatisticsFormat(const db::IdType& user_id, const db::Period& period) = 0;
	void set_facade(db::IDbFacade::Ptr&& facade);
protected:
	db::IDbFacade::Ptr m_facade;
};
