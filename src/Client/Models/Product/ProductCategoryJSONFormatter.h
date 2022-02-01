#pragma once

#include "QJsonDocument"
#include "DTO/ProductCategory.h"

class ProductCategoryJSONFormatter
{
public:
	QJsonDocument FormatProductCategory(ProductCategory& category);
};
