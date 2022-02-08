#pragma once

#include "QJsonDocument"
#include "QJsonObject"

#include "Net/Parsing.h"

template <typename Category>
class ProductCategoryJSONParserBase
{
public:
	Category Parse(const QJsonObject& json)
	{
		Category category;
		SafeReadId(json, "id", category.id);
		SafeReadString(json, "name", category.name);
		return category;
	}
};
