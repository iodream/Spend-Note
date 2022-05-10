#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/PeriodicProduct.h"

class RemovePeriodicProductHandler : public AuthorizedHandler
{
public:
	RemovePeriodicProductHandler();
	virtual ~RemovePeriodicProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
};
