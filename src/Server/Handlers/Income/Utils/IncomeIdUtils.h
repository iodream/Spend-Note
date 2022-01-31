#pragma once

#include "../AddIncomeHandler.h"
#include "../libdal/Facade/IDbFacade.h"
#include "Net/Parsing.h"
#include "IncomeCategoryUtils.h"

QJsonDocument FormatIncomeId(const IncomeId& income_id);
