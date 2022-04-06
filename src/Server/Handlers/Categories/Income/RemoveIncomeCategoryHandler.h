#pragma once

#include "../../AuthorizedHandler.h"
#include "../../../libdal/DTOs/Income.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../../Common.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

class RemoveIncomeCategoryHandler : public AuthorizedHandler
{
public:
	RemoveIncomeCategoryHandler() {};
	virtual ~RemoveIncomeCategoryHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
};
