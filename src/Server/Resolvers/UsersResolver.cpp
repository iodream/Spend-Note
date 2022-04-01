#include "UsersResolver.h"

#include "../Handlers/List/GetListsHandler.h"
#include "../Handlers/List/AddListHandler.h"
#include "../Handlers/Income/GetIncomesHandler.h"
#include "../Handlers/Income/AddIncomeHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"
#include "../Handlers/Statistics/GetBalanceHandler.h"
#include "../Handlers/List/GetDailyListHandler.h"
#include "../Handlers/Statistics/GetExpensesPerCategoryHandler.h"
#include "../Handlers/Statistics/GetExpensesPercentagePerCategoryHandler.h"
#include "../Handlers/Statistics/GetExpensesPerDayHandler.h"
#include "../Handlers/Categories/Income/AddIncomeCategoryHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {

const std::string LISTS   = "/lists";
const std::string INCOMES = "/incomes";
const std::string BALANCE = "/balance";
const std::string DAILY_LIST = "/daily-list";
const std::string EXPENSES_PER_CATEGORY = "/expenses-per-category";
const std::string EXPENSES_PERCENTAGE_PER_CATEGORY = "/expenses-percentage-per-category";
const std::string EXPENSES_PER_DAY = "/expenses-per-day";
const std::string INCOME_CATEGORIES = "/income-categories";
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
	else if (segment == EXPENSES_PER_CATEGORY) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetExpensesPerCategoryHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == EXPENSES_PERCENTAGE_PER_CATEGORY) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetExpensesPercentagePerCategoryHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == EXPENSES_PER_DAY) {
		if (method == Net::HTTP_METHOD_GET)
			return new GetExpensesPerDayHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == INCOME_CATEGORIES) {
		if (method == Net::HTTP_METHOD_POST)
			return new AddIncomeCategoryHandler();
		return new MethodNotAllowedHandler();
	}

	return nullptr;
}

ICommandHandler* UsersResolver::ResolveLastSegment(
	const std::string& method)
{
	Q_UNUSED(method);
	return nullptr;
}
