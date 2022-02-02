#pragma once

#include "QJsonDocument"
#include "DTO/ProductId.h"

class ProductIdJSONParser
{
public:
	ProductId ParseProductId(const QJsonObject& json);
};
