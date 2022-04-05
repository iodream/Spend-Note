#include "IncomesResolver.h"

#include "../Handlers/Income/UpdateIncomeHandler.h"
#include "../Handlers/Income/RemoveIncomeHandler.h"
#include "../Handlers/Income/GetIncomeCategoriesHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {

const std::string CATEGORIES = "/categories";

}

ICommandHandler* IncomesResolver::Resolve(
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
		params.Insert(Params::INCOME_ID, Params::Value{income_id});
		return Resolve(path, method, next_pos, params);
	}

	if (segment == CATEGORIES) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetIncomeCategoriesHandler();
		return new MethodNotAllowedHandler();
		}

	return nullptr;
}

ICommandHandler* IncomesResolver::ResolveLastSegment(
	const std::string& method)
{
	SCOPED_LOGGER;
	if (method == Net::HTTP_METHOD_PUT)
		return new UpdateIncomeHandler();
	else if (method == Net::HTTP_METHOD_DELETE)
		return new RemoveIncomeHandler();
	return new MethodNotAllowedHandler();
}
