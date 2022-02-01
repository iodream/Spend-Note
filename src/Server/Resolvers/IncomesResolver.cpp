#include "IncomesResolver.h"

#include "../Handlers/Income/UpdateIncomeHandler.h"
#include "../Handlers/Income/RemoveIncomeHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"

ICommandHandler* IncomesResolver::Resolve(
	const std::string& path,
	const std::string& method,
	std::string::size_type pos,
	Params& params)
{
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

	return nullptr;
}

ICommandHandler* IncomesResolver::ResolveLastSegment(
	const std::string& method)
{
	if (method == Net::HTTP_METHOD_PUT)
		return new UpdateIncomeHandler();
	else if (method == Net::HTTP_METHOD_DELETE)
		return new RemoveIncomeHandler();
	return new MethodNotAllowedHandler();
}
