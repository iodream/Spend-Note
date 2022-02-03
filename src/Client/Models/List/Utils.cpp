#include "Utils.h"
List ParseList(const QJsonObject& json)
{
	List list;

	SafeReadId(json, "list_id", list.list_id);
	SafeReadId(json, "owner_id", list.owner_id);
	SafeReadId(json, "state_id", list.state_id);
	SafeReadString(json, "name", list.name);
	SafeReadString(json, "state", list.state);

	return list;
}

QJsonDocument FormatList(const List& list)
{
	QJsonObject json;

	json["list_id"] = std::to_string(list.list_id).c_str();
	json["owner_id"] = std::to_string(list.owner_id).c_str();
	json["state_id"] = std::to_string(list.state_id).c_str();
	json["name"] = list.name.toStdString().c_str();
	json["state"] = list.state.toStdString().c_str();

	return QJsonDocument{json};
}
