#pragma once

#include "ISubDomainResolver.h"

class IncomesResolver : public ISubDomainResolver
{
public:
	virtual ~IncomesResolver() override {}

	virtual ICommandHandler* Resolve(
		const std::string& path,
		const std::string& method,
		std::string::size_type pos,
		Params& params) override;

	virtual ICommandHandler* ResolveLastSegment(
		const std::string& method) override;
};
