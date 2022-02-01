#pragma once

#include "QJsonDocument"
#include "../../Entities/ProductCategory.h"

class ProductCategoryJSONFormatter
{
public:
	QJsonDocument FormatProductCategory(ProductCategory& category);
};
