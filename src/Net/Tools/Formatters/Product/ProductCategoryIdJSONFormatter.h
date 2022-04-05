#pragma once

#include <QJsonDocument>

#include "Net/Entities/Product/ProductCategoryId.h"

class ProductCategoryIdJSONFormatter
{
public:
	QJsonObject Format(const ProductCategoryId& product_id);
};
