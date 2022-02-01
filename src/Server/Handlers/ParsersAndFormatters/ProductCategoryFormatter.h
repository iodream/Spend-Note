#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <string>

#include "../Entities/ProductCategory.h"
#include "Net/Parsing.h"
#include "../Handlers/Common.h"

QJsonObject ProductCategoryFormatter(ProductCategory& category)
{
	QJsonObject json;
	json["name"] = category.name.c_str();
	SafeWriteId(json, "id", category.id);
}
