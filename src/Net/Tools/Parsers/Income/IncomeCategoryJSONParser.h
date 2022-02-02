#pragma once

#include <QJsonObject>

#include "Net/Entities/Income/IncomeCategory.h"
#include "Net/Parsing.h"

template <typename T>
class IncomeCategoryJSONParser
{
	T Parse(const QJsonObject& json)
	{
		T income_category;
		SafeReadId(json, "id", income_category.id);
		SafeReadString(json, "name", income_category.name);
		return income_category;
	}
};
