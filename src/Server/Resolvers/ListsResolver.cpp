#include "ListsResolver.h"

#include "../Handlers/List/RemoveListHandler.h"
#include "../Handlers/List/UpdateListHandler.h"
#include "../Handlers/Product/GetProductsHandler.h"
#include "../Handlers/Product/AddProductHandler.h"

#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {

const std::string PRODUCTS = "/products";
const std::string CATEGORIES = "/categories";

}

ICommandHandler* ListsResolver::Resolve(
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
		auto list_id = std::stoll(segment.substr(1));
		params.Insert(Params::LIST_ID, Params::Value{list_id});
		return Resolve(path, method, next_pos, params);
	}

	if (segment == PRODUCTS) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetProductsHandler();
		else if (method == Net::HTTP_METHOD_POST)
			return new AddProductHandler();
		return new MethodNotAllowedHandler();
	}

	return nullptr;
}

ICommandHandler* ListsResolver::ResolveLastSegment(
	const std::string& method)
{
	SCOPED_LOGGER;
	if (method == Net::HTTP_METHOD_PUT)
		return new UpdateListHandler();
	else if (method == Net::HTTP_METHOD_DELETE)
		return new RemoveListHandler();
	return new MethodNotAllowedHandler();
}
