#include <utility>

#include "RootResolver.h"

#include "IncomesResolver.h"
#include "ListsResolver.h"
#include "ProductsResolver.h"
#include "UsersResolver.h"

#include "../Handlers/LoginHandler.h"
#include "../Handlers/SignupHandler.h"
#include "../Handlers/MethodNotAllowedHandler.h"

#include "Utils.h"
#include "../Error.h"
#include "Logger/ScopedLogger.h"

namespace {

const std::string LOGIN    = "/login";
const std::string SIGNUP   = "/signup";
const std::string INCOMES  = "/incomes";
const std::string LISTS    = "/lists";
const std::string PRODUCTS = "/products";
const std::string USERS    = "/users";

}

RootResolver::RootResolver()
{
	SCOPED_LOGGER;
//	m_resolvers[INCOMES] =
//		std::unique_ptr<ISubDomainResolver>(new IncomesResolver());
//	m_resolvers[LISTS] =
//		std::unique_ptr<ISubDomainResolver>(new ListsResolver());
//	m_resolvers[PRODUCTS] =
//		std::unique_ptr<ISubDomainResolver>(new ProductsResolver());
	m_resolvers[USERS] =
		std::unique_ptr<ISubDomainResolver>(new UsersResolver());
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

	auto resolver_it = m_resolvers.find(segment);
	if (resolver_it != m_resolvers.end())
		return resolver_it->second->Resolve(path, method, next_pos, params);

	return nullptr;
}