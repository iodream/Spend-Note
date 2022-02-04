#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/List.h"

class RemoveListHandler : public AuthorizedHandler
{
public:
	RemoveListHandler();
	virtual ~RemoveListHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
};
