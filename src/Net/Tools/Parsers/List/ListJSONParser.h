#pragma once
#include <QJsonObject>

#include "ListStateJSONParse.h"
#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"

template <typename T>
class ListJSONParser
{
public:
    T Parse(const QJsonObject& obj)
    {
        T list;
        QJsonObject state_json;

        SafeReadNumber(obj, "id", list.id);
        SafeReadString(obj, "name", list.name);
        SafeReadNumber(obj, "owner_id", list.owner_id);

        SafeReadObject(obj, "state", state_json);

        list.state = m_parser.Parser(state_json);

        return list;
    }

private:
    ListStateJSONParser<T> m_parser{};
};
