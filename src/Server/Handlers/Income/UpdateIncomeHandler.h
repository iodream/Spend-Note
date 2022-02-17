#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Income.h"

class UpdateIncomeHandler : public AuthorizedHandler
{
public:
	UpdateIncomeHandler();
	virtual ~UpdateIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	IncomeJSONParser m_parser{};
};
