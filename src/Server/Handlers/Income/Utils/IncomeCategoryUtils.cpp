#include "IncomeCategoryUtils.h"

IncomeCategoryIn ParseIncomeCategory(const QJsonObject& json_category)
{
  double tmp_number;
  IncomeCategoryIn income_category;

  SafeReadNumber(json_category, "id", tmp_number);
  income_category.id = tmp_number;

  SafeReadString(json_category, "name", income_category.name);

  return income_category;
}

QJsonObject FormatIncomeCategory(std::string name, IdType id)
{
  QJsonObject json;

  json["id"] = id;
  json["name"] = name.c_str();

  return json;
}
