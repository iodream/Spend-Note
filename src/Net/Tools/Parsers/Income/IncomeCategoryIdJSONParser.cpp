#include "IncomeCategoryIdJSONParser.h"

IncomeCategoryId IncomeCategoryIdJSONParser::Parse(const QJsonObject& json)
{
	IncomeCategoryId category_id;
	SafeReadId(json, "id", category_id.id);
	return category_id;
}
