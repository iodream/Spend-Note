#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/PeriodicIncome.h"

class RemovePeriodicIncomeHandler : public AuthorizedHandler
{
public:
	RemovePeriodicIncomeHandler();
	virtual ~RemovePeriodicIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
};
