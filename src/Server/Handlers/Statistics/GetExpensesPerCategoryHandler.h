#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Statistics.h"

class GetExpensesPerCategoryHandler : public AuthorizedHandler
{
public:
	GetExpensesPerCategoryHandler();
	virtual ~GetExpensesPerCategoryHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	StatisticsPerCategoryJSONFormatter m_formatter;
};
