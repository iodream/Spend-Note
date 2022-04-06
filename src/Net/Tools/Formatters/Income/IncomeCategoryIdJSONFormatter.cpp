#include "IncomeCategoryIdJSONFormatter.h"

QJsonDocument IncomeCategoryIdJSONFormatter::Format(const IncomeCategoryId& category_id)
{
	QJsonObject json;
	WriteId(json, "id", category_id.id);
	return QJsonDocument{json};
}
