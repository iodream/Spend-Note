#include "IncomeUtils.h"

Income ParseIncome(const QJsonObject& json)
{
  double tmp_number;
  Income income;

  SafeReadNumber(json, "id", tmp_number);
  income.id = tmp_number;

  QJsonObject json_category = json["category"].toObject();
  income.category = ParseIncomeCategory(json_category);

  SafeReadQString(json, "name", income.name);
  SafeReadNumber(json, "amount", income.amount);

  SafeReadQString(json, "add_time", income.add_time);
  SafeReadQString(json, "expiration_time", income.expiration_time);

  return income;
}

QJsonDocument FormatIncome(const Income& income)
{
  QJsonObject json, category;

  json["id"] = income.id;
  json["category"] = FormatIncomeCategory(income.category);

  json["name"] = income.name.toStdString().c_str();
  json["amount"] = income.amount;

  json["add_time"] = income.add_time.toStdString().c_str();
  json["expiration_time"] = income.expiration_time.toStdString().c_str();

  return QJsonDocument{json};
}
