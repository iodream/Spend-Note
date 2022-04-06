#include "IncomeCategoriesResolver.h"

#include "../Handlers/Categories/Income/RemoveIncomeCategoryHandler.h"
#include "../Handlers/Categories/Income/UpdateIncomeCategoryHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

ICommandHandler* IncomeCategoriesResolver::Resolve(
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
		auto income_category_id = std::stoll(segment.substr(1));
		params.Insert(Params::INCOME_CATEGORY_ID, Params::Value{income_category_id});
		return Resolve(path, method, next_pos, params);
	}

	return nullptr;
}

ICommandHandler* IncomeCategoriesResolver::ResolveLastSegment(
	const std::string& method)
{
	SCOPED_LOGGER;
	if (method == Net::HTTP_METHOD_PUT)
		return new UpdateIncomeCategoryHandler();
	else if (method == Net::HTTP_METHOD_DELETE)
		return new RemoveIncomeCategoryHandler();
	return new MethodNotAllowedHandler();
}
