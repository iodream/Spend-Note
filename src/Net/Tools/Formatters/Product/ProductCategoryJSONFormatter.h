#pragma once

#include "QJsonDocument"
#include "QJsonObject"

#include "Net/Parsing.h"
#include "../../../Entities/ProductCategory.h"

template <typename Entity>
class ProductCategoryJSONFormatter
{
public:
	QJsonDocument Format(const Entity& category)
	{
		QJsonObject json;
		WriteString(json, "name", category.name);
		WriteId(json, "id", category.id);
		return QJsonDocument{json};
	}
};
