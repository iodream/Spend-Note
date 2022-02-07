#include "ListIdJSONFormatter.h"

QJsonObject ListIdJSONFormatter::Format(const ListId& list_id)
{
	QJsonObject json;
	WriteId(json, "id", list_id.id);
	return json;
}
