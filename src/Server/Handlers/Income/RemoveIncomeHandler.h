#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Income.h"

class RemoveIncomeHandler : public AuthorizedHandler
{
public:
	RemoveIncomeHandler();
	virtual ~RemoveIncomeHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
};
