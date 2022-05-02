#pragma once

#include "QJsonDocument"
#include "Net/Entities/PeriodicProduct/PeriodicProductId.h"

class PeriodicProductIdJSONParser
{
public:
	PeriodicProductId Parse(const QJsonObject& json);
};
