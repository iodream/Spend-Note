#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/PeriodicProduct.h"

class UpdatePeriodicProductHandler : public AuthorizedHandler
{
public:
	UpdatePeriodicProductHandler();
	virtual ~UpdatePeriodicProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductJSONParser m_parser{};
};
