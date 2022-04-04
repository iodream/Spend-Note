#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../../AuthorizedHandler.h"

#include "../../Entities/Entities.h"
#include "../../Entities/Parsers.h"
#include "../../Entities/Formatters.h"

#include "../../../libdal/DTOs/Product.h"

class UpdateProductCategoryHandler : public AuthorizedHandler
{
public:
	UpdateProductCategoryHandler();
	virtual ~UpdateProductCategoryHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductCategoryJSONParser m_parser{};
};
