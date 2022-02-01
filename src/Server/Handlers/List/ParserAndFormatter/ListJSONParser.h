#include <QJsonObject>

#include "ListEntity.h"
#include "../Net/Parsing.h"

class ListJSONParser
{
public:
    ListEntity Parse(const QJsonObject& obj);
};

ListEntity ListJSONParser::Parse(const QJsonObject& obj)
{
    ListEntity list;

    SafeReadId(obj, "id", list.id);
    SafeReadString(obj, "name", list.name);
    SafeReadId(obj, "owner_id", list.owner_id);

    QJsonObject tmp_obj = obj["state"].toObject();

    SafeReadId(tmp_obj, "id", list.state.first);
    SafeReadString(tmp_obj, "name", list.state.second);

    return list;
}
