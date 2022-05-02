#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"

class RemoveProductHandler : public AuthorizedHandler
{
public:
	RemoveProductHandler();
	virtual ~RemoveProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
};
