#pragma once

#include <QJsonObject>

#include "Net/Entities/Income/IncomeCategory.h"

template <typename T>
class IncomeCategoryJSONFormatter
{
	QJsonObject Format(IncomeCategory<T>& income_category)
	{
		QJsonObject json;
		WriteId(json, "id", income_category.id);
		WriteString(json, "name", income_category.name);
		return json;
	}
};
