#pragma once

#include <QJsonObject>

#include "../Income/AddIncomeHandler.h"

Income ParseIncome(const QJsonObject& json);
