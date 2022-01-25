#include "Utils.h"

Income ParseIncome(const QJsonObject& json)
{
	Income income;

	SafeReadId(json, "income_id", income.income_id);
	SafeReadId(json, "owner_id", income.owner_id);
	SafeReadQString(json, "name", income.name);
	SafeReadNumber(json, "amount", income.amount);
	SafeReadId(json, "category_id", income.category_id);
	SafeReadQString(json, "add_time", income.add_time);
	SafeReadQString(json, "expiration_time", income.expiration_time);

	return income;
}

QJsonDocument FormatIncome(const Income& income)
{
	QJsonObject json;

	json["income_id"] = std::to_string(income.income_id).c_str();
	json["owner_id"] = std::to_string(income.owner_id).c_str();
	json["name"] = income.name;
	json["amount"] = income.amount;
	json["category_id"] = std::to_string(income.category_id).c_str();
	json["add_time"] = income.add_time.toStdString().c_str();
	json["expiration_time"] = income.expiration_time.toStdString().c_str();

	return QJsonDocument{json};
}
