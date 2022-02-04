#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Parsing.h"

template <typename Category>
class ProductCategoryJSONFormatterBase
{
public:
	QJsonObject Format(const Category& category)
	{
		QJsonObject json;
		WriteString(json, "name", category.name);
		WriteId(json, "id", category.id);
		return json;
	}
};
