#include "PeriodicProductsResolver.h"

#include "../Handlers/PeriodicProduct/RemovePeriodicProductHandler.h"
#include "../Handlers/PeriodicProduct/UpdatePeriodicProductHandler.h"
#include "../Handlers/PeriodicProduct/GetProductsForPeriodicProductHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {
	const std::string PRODUCTS = "/products";
}

ICommandHandler* PeriodicProductsResolver::Resolve(
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
		auto product_id = std::stoll(segment.substr(1));
		params.Insert(Params::PERIODIC_PRODUCT_ID, Params::Value{product_id});
		return Resolve(path, method, next_pos, params);
	}

	if (segment == PRODUCTS) {
		if (method == Net::HTTP_METHOD_GET)
		{
			return new GetProductsForPeriodicProductHandler();
		}
		return new MethodNotAllowedHandler();
	}

	return nullptr;
}

ICommandHandler* PeriodicProductsResolver::ResolveLastSegment(
	const std::string& method)
{
	SCOPED_LOGGER;
	if (method == Net::HTTP_METHOD_PUT)
		return new UpdatePeriodicProductHandler();
	else if (method == Net::HTTP_METHOD_DELETE)
		return new RemovePeriodicProductHandler();
	return new MethodNotAllowedHandler();
}
