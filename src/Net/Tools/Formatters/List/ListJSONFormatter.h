#pragma once
#include <QJsonObject>

#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"
#include "ListStateJSONFormatter.h"

template<class T>
class ListJSONFormatter
{
public:
    QJsonDocument Format(const ListEntity<T>& list)
    {
        QJsonObject json, tmp_json;

        WriteId(json, "id", list.id);
        WriteId(json, "owner_id", list.owner_id);
        WriteString(json, "name", list.name);

        json["state"] = m_formatter.Format(list.state).object();

        return  QJsonDocument{json};
    }

private:
    ListStateJSONFormatter<T> m_formatter{};
};
