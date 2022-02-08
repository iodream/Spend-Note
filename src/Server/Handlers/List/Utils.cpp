#include "Utils.h"

#include "Net/Parsing.h"
#include "Logger/ScopedLogger.h"

db::List ParseList(const QJsonObject& json)
{
	SCOPED_LOGGER;
	db::List list;

	std::string tmp_date;
	SafeReadId(json, "list_id", list.id);
	SafeReadId(json, "owner_id", list.owner_id);
	SafeReadId(json, "state_id", list.state_id);
	SafeReadString(json, "name", list.name);
	return list;
}
