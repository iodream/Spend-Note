#pragma once

#include <QJsonObject>

template <typename Category>
class IncomeCategoryJSONFormatterBase
{
public:
	QJsonObject Format(const Category& income_category)
	{
		QJsonObject json;
		WriteId(json, "id", income_category.id);
		WriteString(json, "name", income_category.name);
		return json;
	}
};
