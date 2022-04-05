#pragma once

#include "ISubDomainResolver.h"
#include "ParametersParsers/StatisticsParametersParser.h"

class UsersResolver : public ISubDomainResolver
{
public:
	virtual ~UsersResolver() override {}

	virtual ICommandHandler* Resolve(
		const std::string& path,
		const std::string& method,
		std::string::size_type pos,
		Params& params) override;

	virtual ICommandHandler* ResolveLastSegment(
		const std::string& method) override;
private:
	StatisticsParametersParser m_statistics_par_parser;
};
