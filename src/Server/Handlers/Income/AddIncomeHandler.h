#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Income.h"

class AddIncomeHandler : public AuthorizedHandler
{
public:
	AddIncomeHandler();
	virtual ~AddIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	IncomeJSONParser m_parser{};
	IncomeIdJSONFormatter m_formatter{};
};
