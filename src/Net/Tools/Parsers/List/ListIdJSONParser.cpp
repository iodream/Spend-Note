#include "ListIdJSONParser.h"

ListId ListIdJSONParser::Parse(const QJsonObject& obj)
{
	ListId list_id;
	SafeReadId(obj, "id", list_id.id);
	return list_id;
}
