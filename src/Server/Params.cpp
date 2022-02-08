#include "Params.h"

#include "Error.h"
#include "Logger/ScopedLogger.h"

const std::string Params::USER_ID = "user-id";
const std::string Params::LIST_ID = "list-id";
const std::string Params::PRODUCT_ID = "product-id";
const std::string Params::INCOME_ID = "income-id";


void Params::Insert(const std::string& key, Value&& value)
{
	SCOPED_LOGGER;
	auto preventer = m_data.find(key);

	if (preventer != m_data.end()) {
		throw InternalError(
			std::string{"Failed to parse parameters. Parameter \""}.
			append(key).
			append(std::string("\" already exists")));
	}
	m_data.insert({key, std::move(value)});
}

Params::Value Params::Get(const std::string& key)
{
	SCOPED_LOGGER;
	auto value = m_data.find(key);

	if (value == m_data.end()) {
		throw InternalError(
			std::string{"No such parameter \""}.
			append(key).
			append(std::string("\"")));
	}

	return value->second;
}
