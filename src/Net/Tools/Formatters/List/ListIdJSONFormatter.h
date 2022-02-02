#pragma once
#include <QJsonObject>

#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"

template<class T>
class ListIdJSONFormatter
{
public:
    QJsonDocument Format(const ListEntity<T>& list)
    {
        QJsonObject json;
        WriteId(json, "id", list.id);
        return QJsonDocument{json};
    };
};
