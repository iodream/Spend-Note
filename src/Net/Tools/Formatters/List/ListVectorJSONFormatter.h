#pragma once
#include <QJsonObject>

#include "../Net/Entities/List.h"
#include "../Net/Parsing.h"
#include "ListJSONFormatter.h"

template<class T>
class ListVectorJSONFormatter
{
public:
    QJsonDocument Format(const std::vector<ListEntity<T>> &lists)
    {

        QJsonObject json;
        QJsonArray out_lists;

        for (const auto& dto_item : lists)
        {
            out_lists.append(m_formatter.Format(dto_item).object());
        }
        json["lists"] = out_lists;

        return QJsonDocument{json};
    };

private:
    ListJSONFormatter<T> m_formatter{};
};
