#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/PeriodicIncome.h"

class UpdatePeriodicIncomeHandler : public AuthorizedHandler
{
public:
	UpdatePeriodicIncomeHandler();
	virtual ~UpdatePeriodicIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	PeriodicIncomeJSONParser m_parser{};
};
