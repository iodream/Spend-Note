#pragma once
#include <QJsonObject>

#include "../Net/Entities/ListId.h"
#include "../Net/Parsing.h"

class ListIdJSONParser
{
public:
    ListId Parser(const QJsonObject& obj)
    {
        ListId list_id;
        SafeReadId(obj, "id", list_id.id);
        return list_id;
    }
};
