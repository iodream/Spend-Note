#pragma once

#include "DTO/IncomeCategory.h"

#include "Net/Parsing.h"

IncomeCategory ParseIncomeCategory(const QJsonObject& json_category);

QJsonObject FormatIncomeCategory(const IncomeCategory& income_category);
