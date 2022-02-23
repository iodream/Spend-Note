#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Statistics.h"

class GetExpensesPercentagePerCategoryHandler : public AuthorizedHandler
{
public:
	GetExpensesPercentagePerCategoryHandler();
	virtual ~GetExpensesPercentagePerCategoryHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ExpensesPercentagePerCategoryJSONFormatter m_formatter;
};
