#pragma once

#include "ISubDomainResolver.h"

class ListsResolver : public ISubDomainResolver
{
public:
	virtual ~ListsResolver() override {}

	virtual ICommandHandler* Resolve(
		const std::string& path,
		const std::string& method,
		std::string::size_type pos,
		Params& params) override;

	virtual ICommandHandler* ResolveLastSegment(
		const std::string& method) override;
};
