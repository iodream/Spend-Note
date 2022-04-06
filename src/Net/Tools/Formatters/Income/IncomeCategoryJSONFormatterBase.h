#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Parsing.h"

template <typename Category>
class IncomeCategoryJSONFormatterBase
{
public:
	QJsonObject Format(const Category& income_category)
	{
		QJsonObject json;
		WriteString(json, "name", income_category.name);
		WriteId(json, "id", income_category.id);
		return json;
	}
};
