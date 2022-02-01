#pragma once

#include <unordered_map>
#include <memory>

#include "ISubDomainResolver.h"
#include "../Params.h"

class RootResolver
{
public:
	RootResolver();
	~RootResolver() {}

	ICommandHandler* Resolve(
		const std::string& path,
		const std::string& method,
		Params& params);
private:
	std::unordered_map<std::string, std::unique_ptr<ISubDomainResolver>> m_resolvers;
};
