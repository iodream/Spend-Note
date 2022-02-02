#pragma once

#include "QJsonDocument"
#include "../../Entities/Product.h"

class ProductJSONFormatter
{
public:
	QJsonDocument FormatProduct(Product& product);
};
