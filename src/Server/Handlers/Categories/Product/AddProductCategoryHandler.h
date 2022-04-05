#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../../AuthorizedHandler.h"

#include "../../Entities/Entities.h"
#include "../../Entities/Parsers.h"
#include "../../Entities/Formatters.h"

#include "../libdal/DTOs/ProductCategory.h"

class AddProductCategoryHandler : public AuthorizedHandler
{
public:
	AddProductCategoryHandler();
	virtual ~AddProductCategoryHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductCategoryJSONParser m_parser{};
	ProductCategoryIdJSONFormatter m_formatter{};
};
