#pragma once

#include "QJsonDocument"
#include "Net/Entities/Statistics/Balance.h"

class BalanceJSONParser
{
public:
	Balance Parse(const QJsonObject& json);
};
