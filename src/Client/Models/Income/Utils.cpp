#include "Utils.h"

Income ParseIncome(const QJsonObject& json)
{
	long long tmp;
	Income income;

	SafeReadId(json, "income_id", income.income_id);
	SafeReadId(json, "owner_id", income.owner_id);
	SafeReadQString(json, "name", income.name);

	SafeReadId(json, "amount", tmp); //currently reading amount as Money (long long)
	income.amount = tmp/100;

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
	json["amount"] = income.amount*100;
	json["category_id"] = std::to_string(income.category_id).c_str();
	json["add_time"] = income.add_time.toStdString().c_str();
	json["expiration_time"] = income.expiration_time.toStdString().c_str();

	return QJsonDocument{json};
}
