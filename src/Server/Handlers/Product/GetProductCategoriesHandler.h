#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/ProductCategory.h"

class GetProductCategoriesHandler : public AuthorizedHandler
{
public:
	GetProductCategoriesHandler();
	virtual ~GetProductCategoriesHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductCategoriesJSONFormatter m_formatter;
};
