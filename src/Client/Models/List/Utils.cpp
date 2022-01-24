#include "Utils.h"

List ParseList(const QJsonObject& json)
{
	List list;

	SafeReadId(json, "list_id", list.list_id);
	SafeReadId(json, "owner_id", list.owner_id);
	SafeReadId(json, "state_id", list.state_id);
	SafeReadQString(json, "name", list.name);
	SafeReadQString(json, "state", list.state);

	return list;
}
