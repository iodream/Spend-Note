#pragma once

#include "QJsonDocument"
#include "Net/Entities/Product/ProductCategoryId.h"

class ProductCategoryIdJSONParser
{
public:
	ProductCategoryId Parse(const QJsonObject& json);
};
