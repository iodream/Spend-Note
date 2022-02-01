#pragma once

#include "QJsonDocument"
#include "../../Entities/ProductId.h"

class ProductIdJSONFormatter
{
public:
	QJsonDocument FormatProductId(ProductId& product_id);
};
