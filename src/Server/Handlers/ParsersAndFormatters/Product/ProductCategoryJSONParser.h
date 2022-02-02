#pragma once

#include "QJsonDocument"
#include "../../Entities/ProductCategory.h"

class ProductCategoryJSONParser
{
public:
	ProductCategory ParseProductCategory(const QJsonObject& json);
};
