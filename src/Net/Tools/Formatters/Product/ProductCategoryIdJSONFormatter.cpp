#include <QJsonObject>

#include "ProductCategoryIdJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject ProductCategoryIdJSONFormatter::Format(const ProductCategoryId& product_category_id)
{
	QJsonObject json;
	WriteId(json, "id", product_category_id.id);
	return json;
}
