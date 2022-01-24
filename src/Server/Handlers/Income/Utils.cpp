#include "Utils.h"
#include "Net/Parsing.h"

Income ParseIncome(const QJsonObject& json)
{
	std::string tmp;
	Income income;

	SafeReadId(json, "user_id", income.user_id);
	SafeReadString(json, "name", income.name);
	SafeReadNumber(json, "amount", income.amount);
	SafeReadId(json, "category_id", income.category_id);

	SafeReadString(json, "add_time", income.add_time);
	SafeReadString(json, "expiration_time", tmp);
	income.expiration_time = (tmp != "")?
		std::optional<Timestamp>(tmp) : std::nullopt;

	return income;
}
