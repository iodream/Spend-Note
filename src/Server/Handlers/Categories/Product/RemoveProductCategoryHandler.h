#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../../AuthorizedHandler.h"
#include "../../../libdal/DTOs/Product.h"

class RemoveProductCategoryHandler : public AuthorizedHandler
{
public:
	RemoveProductCategoryHandler();
	virtual ~RemoveProductCategoryHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
};
