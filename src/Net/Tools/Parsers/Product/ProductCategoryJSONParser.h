#pragma once

#include "QJsonDocument"
#include "QJsonObject"

#include "Net/Parsing.h"
#include "../../../Entities/ProductCategory.h"

template <typename Entity>
class ProductCategoryJSONParser
{
public:
	Entity Parse(const QJsonDocument& json_doc)
	{
		Entity category;
		QJsonObject json = json_doc.object();
		SafeReadId(json, "id", category.id);
		SafeReadString(json, "name", category.name);
		return category;
	}
};
