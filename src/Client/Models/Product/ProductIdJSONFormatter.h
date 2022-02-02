#pragma once

#include "QJsonDocument"
#include "DTO/ProductId.h"

class ProductIdJSONFormatter
{
public:
	QJsonDocument FormatProductId(ProductId& product_id);
};
