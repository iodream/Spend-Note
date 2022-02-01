#include <QJsonObject>

#include "ListEntity.h"
#include "../Net/Parsing.h"
#include "ListJSONParser.h"

class ListJSONFormatter
{
public:
    QJsonDocument Format(const ListEntity& list);
    QJsonDocument Format(const std::vector<ListEntity>& lists);
    QJsonDocument FormatId(const ListEntity& list);
};

QJsonDocument ListJSONFormatter::Format(const ListEntity& list)
{
    QJsonObject json, tmp_json;

    json["id"] = std::to_string(list.id).c_str();
    json["name"] = list.name.c_str();
    json["owner_id"] = std::to_string(list.owner_id).c_str();

    tmp_json["id"] = std::to_string(list.state.first).c_str();
    tmp_json["name"] = list.state.second.c_str();

    json["state"] = tmp_json;

    return  QJsonDocument{json};
}

QJsonDocument ListJSONFormatter::Format(const std::vector<ListEntity> &lists)
{

    QJsonObject json;
    QJsonArray out_lists;

    for (const auto& dto_item : lists)
    {
        out_lists.append(Format(dto_item).object());
    }
    json["lists"] = out_lists;

    return QJsonDocument{json};
}

QJsonDocument ListJSONFormatter::FormatId(const ListEntity& list)
{
    QJsonObject json;

    json["id"] = std::to_string(list.id).c_str();

    return QJsonDocument{json};
}
