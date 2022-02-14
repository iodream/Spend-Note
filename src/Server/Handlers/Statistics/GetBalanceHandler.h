#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Product.h"

class GetBalanceHandler : public AuthorizedHandler
{
public:
	GetBalanceHandler();
	virtual ~GetBalanceHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	BalanceJSONFormatter m_formatter;
};
