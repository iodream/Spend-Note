#include "UsersResolver.h"

#include "../Handlers/List/GetListsHandler.h"
#include "../Handlers/List/AddListHandler.h"
#include "../Handlers/Income/GetIncomesHandler.h"
#include "../Handlers/Income/AddIncomeHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"
#include "../Handlers/Statistics/GetBalanceHandler.h"
#include "../Handlers/List/GetDailyListHandler.h"
#include "../Handlers/Categories/Income/AddIncomeCategoryHandler.h"
#include "../Handlers/Categories/Income/GetIncomeCategoriesHandler.h"
#include "../Handlers/Categories/Product/GetProductCategoriesHandler.h"
#include "../Handlers/Categories/Product/AddProductCategoryHandler.h"
#include "../Handlers/Statistics/GetStatisticsHandler.h"
#include "../Handlers/Product/GetRecommendationProductHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {

const std::string LISTS   = "/lists";
const std::string INCOMES = "/incomes";
const std::string BALANCE = "/balance";
const std::string DAILY_LIST = "/daily-list";
const std::string INCOME_CATEGORIES = "/income-categories";
const std::string PRODUCT_CATEGORIES = "/product-categories";
const std::string STATISTICS = "/statistics";
const std::string RECOMMENDATION = "/recommendation";
}

ICommandHandler* UsersResolver::Resolve(
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
		auto user_id = std::stoll(segment.substr(1));
		params.Insert(Params::USER_ID, Params::Value{user_id});
		return Resolve(path, method, next_pos, params);
	}

	if (segment == LISTS) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetListsHandler();
		else if (method == Net::HTTP_METHOD_POST)
			return new AddListHandler();
		return new MethodNotAllowedHandler();;
	}
	else if (segment == INCOMES) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetIncomesHandler();
		else if (method == Net::HTTP_METHOD_POST)
			return new AddIncomeHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == BALANCE) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetBalanceHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == DAILY_LIST) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetDailyListHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == INCOME_CATEGORIES) {
		if (method == Net::HTTP_METHOD_POST)
			return new AddIncomeCategoryHandler();
		else if (method == Net::HTTP_METHOD_GET)
			return new GetIncomeCategoriesHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == PRODUCT_CATEGORIES) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetProductCategoriesHandler();
		else if (method == Net::HTTP_METHOD_POST)
			return new AddProductCategoryHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == RECOMMENDATION) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetRecommendationProductHandler();
		return new MethodNotAllowedHandler();
	}
	auto statistics = segment.find(STATISTICS);
	if (statistics != std::string::npos) {
		m_statistics_par_parser.Parse(segment, params);
		if (method == Net::HTTP_METHOD_GET)
			return new GetStatisticsHandler();
	}
	return nullptr;
}

ICommandHandler* UsersResolver::ResolveLastSegment(
	const std::string& method)
{
	Q_UNUSED(method);
	return nullptr;
}
