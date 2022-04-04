#include <QJsonObject>

#include "Net/Parsing.h"
#include "ProductCategoryIdJSONParser.h"

ProductCategoryId ProductCategoryIdJSONParser::Parse(const QJsonObject& json)
{
	ProductCategoryId product_category_id;
	SafeReadId(json, "id", product_category_id.id);
	return product_category_id;
}
