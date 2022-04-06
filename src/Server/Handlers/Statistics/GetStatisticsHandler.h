#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
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
