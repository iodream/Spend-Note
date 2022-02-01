#pragma once

#include "QJsonDocument"
#include "DTO/ProductCategory.h"

class ProductCategoryJSONParser
{
public:
	ProductCategory ParseProductCategory(const QJsonObject& json);
};
