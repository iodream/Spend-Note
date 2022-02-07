#pragma once

#include "QJsonDocument"
#include "Net/Entities/Product/ProductId.h"

class ProductIdJSONParser
{
public:
	ProductId Parse(const QJsonObject& json);
};
