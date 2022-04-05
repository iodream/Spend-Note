#pragma once

#include "ISubDomainResolver.h"

class ProductCategoriesResolver : public ISubDomainResolver
{
public:
	virtual ~ProductCategoriesResolver() override {}

	virtual ICommandHandler* Resolve(
		const std::string& path,
		const std::string& method,
		std::string::size_type pos,
		Params& params) override;

	virtual ICommandHandler* ResolveLastSegment(
		const std::string& method) override;
};
