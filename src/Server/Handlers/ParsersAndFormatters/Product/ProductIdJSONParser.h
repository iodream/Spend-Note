#pragma once

#include "QJsonDocument"
#include "../../Entities/ProductId.h"

class ProductIdJSONParser
{
public:
	ProductId ParseProductId(const QJsonObject& json);
};
