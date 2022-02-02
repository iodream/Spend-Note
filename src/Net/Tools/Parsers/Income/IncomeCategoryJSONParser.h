#pragma once

#include <QJsonObject>

#include "Net/Entities/Income/IncomeCategory.h"
#include "Net/Parsing.h"

template <typename Entity>
class IncomeCategoryJSONParser
{
public:
	Entity Parse(const QJsonObject& json)
	{
		Entity income_category;
		SafeReadId(json, "id", income_category.id);
		SafeReadString(json, "name", income_category.name);
		return income_category;
	}
};
