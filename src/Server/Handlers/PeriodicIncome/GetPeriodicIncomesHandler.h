#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/PeriodicIncome.h"

class GetPeriodicIncomesHandler : public AuthorizedHandler
{
public:
	GetPeriodicIncomesHandler();
	virtual ~GetPeriodicIncomesHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	PeriodicIncomesJSONFormatter m_formatter;
};
