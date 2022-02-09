#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Product.h"

class GetProductsHandler : public AuthorizedHandler
{
public:
	GetProductsHandler();
	virtual ~GetProductsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductsJSONFormatter m_formatter;
};
