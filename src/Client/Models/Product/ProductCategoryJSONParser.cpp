#include <QJsonObject>

#include "Net/Parsing.h"
#include "ProductCategoryJSONParser.h"

ProductCategory ProductCategoryJSONParser::ParseProductCategory(const QJsonObject &json)
{
	ProductCategory category;
	SafeReadId(json, "id", category.id);
	SafeReadQString(json, "name", category.name);
	return category;
}
