#include "ListJSONParser.h"

ListEntity ListJSONParser::Parse(const QJsonObject& obj)
{
    ListEntity list;
    double tmp_var;

    SafeReadNumber(obj, "id", tmp_var);
    list.id = tmp_var;
    SafeReadString(obj, "name", list.name);
    SafeReadNumber(obj, "owner_id", tmp_var);
    list.owner_id = tmp_var;

    QJsonObject tmp_obj = obj["state"].toObject();

    SafeReadNumber(tmp_obj, "id", tmp_var);
    list.state.first = tmp_var;
    SafeReadString(tmp_obj, "name", list.state.second);

    return list;
}
