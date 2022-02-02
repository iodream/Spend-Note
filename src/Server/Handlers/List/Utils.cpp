#include "Utils.h"
#include "ParserAndFormatter/ListEntity.h"

#include "Net/Parsing.h"

List ParseList(const QJsonObject& json)
{
	List list;

	std::string tmp_date;
	SafeReadId(json, "list_id", list.id);
	SafeReadId(json, "owner_id", list.owner_id);
	SafeReadId(json, "state_id", list.state_id);
	SafeReadString(json, "name", list.name);
	return list;
}
