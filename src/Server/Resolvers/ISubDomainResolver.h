#pragma once

#include <string>
#include <vector>

#include "../Handlers/ICommandHandler.h"
#include "../Params.h"

class ISubDomainResolver
{
public:
	ISubDomainResolver() {}
	virtual ~ISubDomainResolver() {}

	virtual ICommandHandler* Resolve(
		const std::string& path,
		const std::string& method,
		std::string::size_type pos,
		Params& params) = 0;

	virtual ICommandHandler* ResolveLastSegment(
		const std::string& method) = 0;
};
