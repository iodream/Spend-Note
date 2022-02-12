#pragma once

#include <QJsonDocument>

#include "Net/Entities/Statistics/Balance.h"

class BalanceJSONFormatter
{
public:
	QJsonObject Format(const Balance& balance);
};
