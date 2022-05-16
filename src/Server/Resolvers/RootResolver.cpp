#include <utility>

#include "RootResolver.h"

#include "IncomesResolver.h"
#include "ListsResolver.h"
#include "ProductsResolver.h"
#include "UsersResolver.h"
#include "IncomeCategoriesResolver.h"
#include "ProductCategoriesResolver.h"
#include "PeriodicIncomesResolver.h"
#include "PeriodicProductsResolver.h"

#include "../Handlers/LoginHandler.h"
#include "../Handlers/SignupHandler.h"
#include "../Handlers/Verification/AddVerificationHandler.h"
#include "../Handlers/Verification/CheckVerificationHandler.h"
#include "../Handlers/User/ChangePasswordHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"
#include "../Handlers/User/ChangeEmailHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {

const std::string LOGIN = "/login";
const std::string SIGNUP = "/signup";
const std::string VERIFICATION = "/verification";
const std::string INCOMES = "/incomes";
const std::string PERIODIC_INCOMES  = "/periodic-incomes";
const std::string LISTS = "/lists";
const std::string PRODUCTS = "/products";
const std::string PERIODIC_PRODUCTS = "/periodic-products";
const std::string USERS = "/users";
const std::string INCOME_CATEGORIES = "/income-categories";
const std::string PRODUCT_CATEGORIES = "/product-categories";
const std::string PASSWORD = "/password";
const std::string EMAIL = "/email";
}

RootResolver::RootResolver()
{
	SCOPED_LOGGER;
	m_resolvers[INCOMES] =
		std::unique_ptr<ISubDomainResolver>(new IncomesResolver());
	m_resolvers[PERIODIC_INCOMES] =
		std::unique_ptr<ISubDomainResolver>(new PeriodicIncomesResolver());
	m_resolvers[LISTS] =
		std::unique_ptr<ISubDomainResolver>(new ListsResolver());
	m_resolvers[PRODUCTS] =
		std::unique_ptr<ISubDomainResolver>(new ProductsResolver());
	m_resolvers[USERS] =
		std::unique_ptr<ISubDomainResolver>(new UsersResolver());
	m_resolvers[INCOME_CATEGORIES] =
		std::unique_ptr<ISubDomainResolver>(new IncomeCategoriesResolver());
	m_resolvers[PRODUCT_CATEGORIES] =
		std::unique_ptr<ISubDomainResolver>(new ProductCategoriesResolver());
	m_resolvers[PERIODIC_PRODUCTS] =
		std::unique_ptr<ISubDomainResolver>(new PeriodicProductsResolver());
}

ICommandHandler* RootResolver::Resolve(
	const std::string& path,
	const std::string& method,
	Params& params)
{
	SCOPED_LOGGER;
	std::string::size_type next_pos;
	auto segment = GetSegment(path, 0, next_pos);

	if (segment == LOGIN) {
		if (method == Net::HTTP_METHOD_POST)
			return new LoginHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == SIGNUP) {
		if (method == Net::HTTP_METHOD_POST)
			return new SignupHandler();
		return new MethodNotAllowedHandler();
	}
	else if (segment == VERIFICATION) {
		if (method == Net::HTTP_METHOD_POST)
			return new AddVerificationHandler();
		if (method == Net::HTTP_METHOD_PUT)
			return new CheckVerificationHandler();
		return new MethodNotAllowedHandler();
	}
	else if(segment == PASSWORD){
		if(method == Net::HTTP_METHOD_PUT)
			return new ChangePasswordHandler();
    return new MethodNotAllowedHandler();
  }
	else if (segment == EMAIL) {
		if(method == Net::HTTP_METHOD_PUT)
			return new ChangeEmailHandler();
		return new MethodNotAllowedHandler();
	}

	auto resolver_it = m_resolvers.find(segment);
	if (resolver_it != m_resolvers.end())
		return resolver_it->second->Resolve(path, method, next_pos, params);

	return nullptr;
}
