#include "IStatisticsFormatter.h"

void IStatisticsFormatter::set_facade(db::IDbFacade::Ptr&& facade)
{
	m_facade = std::move(facade);
}
