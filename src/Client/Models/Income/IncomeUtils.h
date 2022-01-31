#pragma once

#include "DTO/Income.h"
#include "IncomeCategoryUtils.h"
#include "Net/Parsing.h"

Income ParseIncome(const QJsonObject& json);

QJsonDocument FormatIncome(const Income& income);
