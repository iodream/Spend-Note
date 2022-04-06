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
	const static std::string PRODUCT_CATEGORY_ID;
	const static std::string INCOME_ID;
	const static std::string INCOME_CATEGORY_ID;
	const static std::string STATISTICS_TYPE;
	const static std::string STATISTICS_PERIOD;
	const static std::string STATISTICS_FORMAT;

private:
	std::unordered_map<std::string, Value> m_data;
};
