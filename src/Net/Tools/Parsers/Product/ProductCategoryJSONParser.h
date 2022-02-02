#pragma once

#include "QJsonDocument"
#include "QJsonObject"

#include "Net/Parsing.h"
#include "../../../Entities/ProductCategory.h"

template <typename T>
class ProductCategoryJSONParser
{
public:
	T Parse(const QJsonObject& json)
	{
		T category;
		SafeReadId(json, "id", category.id);
		SafeReadString(json, "name", category.name);
		return category;
	}
};
