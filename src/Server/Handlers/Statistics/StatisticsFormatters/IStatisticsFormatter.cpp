#include "IStatisticsFormatter.h"

IStatisticsFormatter::IStatisticsFormatter(db::IDbFacade::Ptr&& facade) {
	m_facade = std::move(facade);
}
