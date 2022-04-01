#pragma once

#include "ISubDomainResolver.h"

//#include "../Handlers/Categories/Product/RemoveIncomeCategoryHandler.h"
//#include "../Handlers/Categories/Product/UpdateIncomeCategoryHandler.h"
#include "../Handlers/Categories/Income/AddIncomeCategoryHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

class IncomeCategoriesResolver : public ISubDomainResolver
{
public:
	virtual ~IncomeCategoriesResolver() override {}

	virtual ICommandHandler* Resolve(
		const std::string& path,
		const std::string& method,
		std::string::size_type pos,
		Params& params) override;

	virtual ICommandHandler* ResolveLastSegment(
		const std::string& method) override;
};
