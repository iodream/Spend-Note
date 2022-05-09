#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Product.h"

class GetProductsForPeriodicProductHandler : public AuthorizedHandler
{
public:
	GetProductsForPeriodicProductHandler();
	virtual ~GetProductsForPeriodicProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductsJSONFormatter m_formatter;
};
