#include "Utils.h"

#include "Net/Parsing.h"

Product ParseList(const QJsonObject& json)
{
    List list;

    double tmp_number;
    std::string tmp_date;
    SafeReadId(json, "list_id", list.list_id);
    SafeReadId(json, "owner_id", list.owner_id);
    SafeReadId(json, "state_id", list.state_id);
    SafeReadString(json, "name", list.name);
    return list;
}
