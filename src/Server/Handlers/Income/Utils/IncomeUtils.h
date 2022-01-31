#pragma once

#include <QJsonObject>

#include "../ParsersAndFormatters/IncomeJSONParser.h"
#include "../libdal/Facade/IDbFacade.h"
#include "Net/Parsing.h"
#include "IncomeCategoryUtils.h"
#include "IncomeIdUtils.h"

IncomeIn ParseIncome(const QJsonObject& json);

QJsonObject FormatIncome(const IncomeOut& income);
