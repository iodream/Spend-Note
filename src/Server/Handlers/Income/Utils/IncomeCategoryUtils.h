#pragma once

#include "IncomeUtils.h"
#include "Net/Parsing.h"

IncomeCategoryIn ParseIncomeCategory(const QJsonObject& json_category);

QJsonObject FormatIncomeCategory(std::string name, IdType id = 0);
