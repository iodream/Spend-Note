#include "ProductsResolver.h"

#include "../Handlers/Product/RemoveProductHandler.h"
#include "../Handlers/Product/UpdateProductHandler.h"
#include "../Handlers/Product/GetProductCategoriesHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {

const std::string CATEGORIES = "/categories";

}

ICommandHandler* ProductsResolver::Resolve(
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
		params.Insert(Params::PRODUCT_ID, Params::Value{product_id});
		return Resolve(path, method, next_pos, params);
	}

	if (segment == CATEGORIES) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetProductCategoriesHandler();
		return new MethodNotAllowedHandler();
		}

	return nullptr;
}

ICommandHandler* ProductsResolver::ResolveLastSegment(
	const std::string& method)
{
	SCOPED_LOGGER;
	if (method == Net::HTTP_METHOD_PUT)
		return new UpdateProductHandler();
	else if (method == Net::HTTP_METHOD_DELETE)
		return new RemoveProductHandler();
	return new MethodNotAllowedHandler();
}
