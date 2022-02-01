#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <string>

#include "../Entities/ProductCategory.h"
#include "Net/Parsing.h"
#include "../Handlers/Common.h"

ProductCategory ProductCategoryParse(QJsonObject& json)
{
	ProductCategory category;
	SafeReadId(json, "id", category.id);
	SafeReadString(json, "name", category.name);
	return category;
}
