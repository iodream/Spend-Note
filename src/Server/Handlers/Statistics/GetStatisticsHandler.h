#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

//#include "../Entities/Entities.h"
//#include "../Entities/Formatters.h"

#include "StatisticsFormatterManager.h"

class GetStatisticsHandler : public AuthorizedHandler
{
public:
	GetStatisticsHandler();
	virtual ~GetStatisticsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	StatisticsFormatterManager m_formatters_manager;
};
