#include "Utils.h"

#include "Net/Parsing.h"

List ListParser(const QJsonObject& json)
{
    List list;

    SafeReadId(json, "list_id", list.list_id);
    SafeReadId(json, "owner_id", list.owner_id);
    SafeReadId(json, "state_id", list.state_id);
    SafeReadString(json, "name", list.name);

    return list;
}
