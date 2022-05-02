#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/PeriodicProduct.h"

class GetPeriodicProductsHandler : public AuthorizedHandler
{
public:
	GetPeriodicProductsHandler();
	virtual ~GetProductsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	PeriodicProductsJSONFormatter m_formatter;
};
