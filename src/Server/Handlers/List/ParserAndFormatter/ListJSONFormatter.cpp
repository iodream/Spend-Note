#include "ListJSONFormatter.h"

QJsonDocument ListJSONFormatter::Format(const ListEntity& list)
{
    QJsonObject json, tmp_json;

    json["id"] = list.id;
    json["name"] = list.name.c_str();
    json["owner_id"] = list.owner_id;

    tmp_json["id"] = list.state.first;
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

    json["id"] = list.id;

    return QJsonDocument{json};
}
