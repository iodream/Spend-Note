#pragma once

#include <unordered_map>
#include <string>
#include <variant>

class Params {
public:
	using Value = std::variant<std::string, long long>;

	void Insert(const std::string& key, Value&& value);
	Value Get(const std::string& key);

	const static std::string USER_ID;
	const static std::string LIST_ID;
	const static std::string PRODUCT_ID;
	const static std::string INCOME_ID;
	const static std::string INCOME_CATEGORY_ID;

private:
	std::unordered_map<std::string, Value> m_data;
};
