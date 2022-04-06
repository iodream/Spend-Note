#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../../AuthorizedHandler.h"

#include "../../Entities/Entities.h"
#include "../../Entities/Formatters.h"

#include "../libdal/DTOs/IncomeCategory.h"

class GetIncomeCategoriesHandler : public AuthorizedHandler
{
public:
	GetIncomeCategoriesHandler();
	virtual ~GetIncomeCategoriesHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	IncomeCategoriesJSONFormatter m_formatter;
};
