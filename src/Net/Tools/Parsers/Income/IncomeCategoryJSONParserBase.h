#pragma once

#include <QJsonObject>

#include "Net/Parsing.h"

template <typename Category>
class IncomeCategoryJSONParserBase
{
public:
	Category Parse(const QJsonObject& json)
	{
		Category income_category;
		SafeReadId(json, "id", income_category.id);
		SafeReadString(json, "name", income_category.name);
		return income_category;
	}
};
