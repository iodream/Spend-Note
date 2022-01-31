#include "IncomeUtils.h"

IncomeIn ParseIncome(const QJsonObject& json)
{
	double tmp_number;
	std::string tmp_date;
	IncomeIn income;

	SafeReadNumber(json, "id", tmp_number);
	income.id = tmp_number;

	QJsonObject category = json["category"].toObject();
	income.category = ParseIncomeCategory(category);

	SafeReadString(json, "name", income.name);
	SafeReadNumber(json, "amount", tmp_number);
	income.amount = tmp_number;

	SafeReadString(json, "add_time", income.add_time);
	SafeReadString(json, "expiration_time", tmp_date);
	income.expiration_time = (tmp_date != "")
		? std::optional<Timestamp>{tmp_date} : std::nullopt;

	return income;
}

QJsonObject FormatIncome(const IncomeOut& income)
{
  QJsonObject json;

  json["id"] = income.id;

  json["category"] = FormatIncomeCategory(income.category_name);
  // no id right now because it is not being returned from GetIncomesHandler

  json["name"] = income.name.c_str();
  json["amount"] = income.amount;
  json["add_time"] = income.add_time.c_str();
  json["expiration_time"] = income.expiration_time.c_str();

  return json;
}
