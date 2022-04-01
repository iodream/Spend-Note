#include "IncomeCategoriesResolver.h"

ICommandHandler* IncomeCategoriesResolver::Resolve(
	const std::string& path,
	const std::string& method,
	std::string::size_type pos,
	Params& params)
{
	SCOPED_LOGGER;

	if (pos == std::string::npos)
	{
		return ResolveLastSegment(method);
	}

	std::string::size_type next_pos;
	auto segment = GetSegment(path, pos, next_pos);

	if (std::isdigit(segment[1]))
	{
		auto income_category_id = std::stoll(segment.substr(1));
		params.Insert(Params::INCOME_CATEGORY_ID, Params::Value{income_category_id});
		return Resolve(path, method, next_pos, params);
	}

	return nullptr;
}

ICommandHandler* IncomeCategoriesResolver::ResolveLastSegment(const std::string& method)
{
	if(method == Net::HTTP_METHOD_POST)
		return new AddIncomeCategoryHandler();
	return new MethodNotAllowedHandler();
}
