#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/PeriodicProduct.h"

class AddPeriodicProductHandler : public AuthorizedHandler
{
public:
	AddPeriodicProductHandler();
	virtual ~AddPeriodicProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	PeriodicProductJSONParser m_parser{};
	PeriodicProductIdJSONFormatter m_formatter{};
};
