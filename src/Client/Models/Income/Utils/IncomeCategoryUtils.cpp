#include "IncomeCategoryUtils.h"

IncomeCategory ParseIncomeCategory(const QJsonObject& json_category)
{
  double tmp_number;
  IncomeCategory income_category;

  SafeReadNumber(json_category, "id", tmp_number);
  income_category.id = tmp_number;

  SafeReadQString(json_category, "name", income_category.name);

  return income_category;
}

QJsonObject FormatIncomeCategory(const IncomeCategory& income_category)
{
  QJsonObject json;

  json["id"] = income_category.id;
  json["name"] = income_category.name.toStdString().c_str();

  return json;
}
