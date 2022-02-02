#pragma once
#include <QJsonObject>

#include "../Net/Entities/ListState.h"
#include "../Net/Parsing.h"

template<class T>
class ListStateJSONParser
{
public:
    T Parser(const QJsonObject& obj)
    {
        T state;

        SafeReadId(obj, "id", state.id);
        SafeReadString(obj, "name", state.name);

        return state;
    }
};
