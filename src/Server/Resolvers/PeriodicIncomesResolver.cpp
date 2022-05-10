#include "PeriodicIncomesResolver.h"

#include "../Handlers/PeriodicIncome/RemovePeriodicIncomeHandler.h"
#include "../Handlers/PeriodicIncome/UpdatePeriodicIncomeHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

ICommandHandler* PeriodicIncomesResolver::Resolve(
	const std::string& path,
	const std::string& method,
	std::string::size_type pos,
	Params& params)
{
	SCOPED_LOGGER;
	if (pos == std::string::npos) {
		return ResolveLastSegment(method);
	}

	std::string::size_type next_pos;
	auto segment = GetSegment(path, pos, next_pos);

	if (std::isdigit(segment[1])) {
		auto income_id = std::stoll(segment.substr(1));
		params.Insert(Params::PERIODIC_INCOME_ID, Params::Value{income_id});
		return Resolve(path, method, next_pos, params);
	}

	return nullptr;
}

ICommandHandler* PeriodicIncomesResolver::ResolveLastSegment(
	const std::string& method)
{
	SCOPED_LOGGER;
	if (method == Net::HTTP_METHOD_PUT)
		return new UpdatePeriodicIncomeHandler();
	else if (method == Net::HTTP_METHOD_DELETE)
		return new RemovePeriodicIncomeHandler();
	return new MethodNotAllowedHandler();
}
