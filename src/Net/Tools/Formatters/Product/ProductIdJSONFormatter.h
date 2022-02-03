#pragma once

#include "QJsonDocument"
#include "../../../Entities/ProductId.h"

class ProductIdJSONFormatter
{
public:
	QJsonDocument Format(const ProductId& product_id);
};
