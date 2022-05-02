#pragma once

#include <QJsonDocument>

#include "Net/Entities/PeriodicProduct/PeriodicProductId.h"

class PeriodicProductIdJSONFormatter
{
public:
	QJsonObject Format(const PeriodicProductId& product_id);
};
