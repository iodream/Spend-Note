#pragma once

#include "QJsonDocument"
#include "DTO/Product.h"

class ProductJSONParser
{
public:
	Product ParseProduct(const QJsonObject& json);
};
