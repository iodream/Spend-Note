#pragma once

#include "DTO/IncomeId.h"
#include "Net/Parsing.h"

IncomeId ParseIncomeId(const QJsonObject& json);
