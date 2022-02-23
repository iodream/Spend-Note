#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Statistics.h"

class GetExpensesPerDayHandler : public AuthorizedHandler
{
public:
	GetExpensesPerDayHandler();
	virtual ~GetExpensesPerDayHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ExpensesPerDayJSONFormatter m_formatter;
};
