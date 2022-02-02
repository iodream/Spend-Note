#pragma once

#include "QJsonDocument"
#include "../../Entities/Product.h"

class ProductJSONParser
{
public:
	Product ParseProduct(const QJsonObject& json);
};
