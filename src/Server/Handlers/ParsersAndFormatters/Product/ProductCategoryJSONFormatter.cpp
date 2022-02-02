#include <QJsonObject>

#include "Net/Parsing.h"
#include "ProductCategoryJSONFormatter.h"

QJsonDocument ProductCategoryJSONFormatter::FormatProductCategory(ProductCategory& category)
{
	QJsonObject json;
	json["name"] = category.name.c_str();
	WriteId(json, "id", category.id);
	return QJsonDocument{json};
}
