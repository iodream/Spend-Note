#pragma once

#include "QJsonDocument"
#include "QJsonObject"

#include "Net/Parsing.h"
#include "../../../Entities/ProductCategory.h"

template <typename T>
class ProductCategoryJSONFormatter
{
public:
	QJsonDocument Format(const T& category)
	{
		QJsonObject json;
		WriteString(json, "name", category.name);
		WriteId(json, "id", category.id);
		return QJsonDocument{json};
	}
};
