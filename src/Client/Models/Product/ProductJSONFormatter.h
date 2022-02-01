#pragma once

#include "QJsonDocument"
#include "DTO/Product.h"

class ProductJSONFormatter
{
public:
	QJsonDocument FormatProduct(Product& product);
};
