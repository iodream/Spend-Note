#pragma once

#include "../../AuthorizedHandler.h"
#include "../../Entities/Entities.h"
#include "../../Entities/Parsers.h"
#include "../../Entities/Formatters.h"
#include "../../Common.h"

#include "../libdal/DTOs/IncomeCategory.h"
#include "../libdal/Exceptions/SQLFailure.h"

#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "Logger/ScopedLogger.h"

#include "Utils.h"

class UpdateIncomeCategoryHandler: public AuthorizedHandler
{
public:
	UpdateIncomeCategoryHandler() {};
	virtual ~UpdateIncomeCategoryHandler() {};

	virtual Net::Response AuthHandle(const Net::Request& request) override;

private:
	IncomeCategoryJSONParser m_parser{};

};
