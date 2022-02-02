#include <QJsonObject>

#include "ListEntity.h"
#include "../Net/Parsing.h"

class ListJSONFormatter
{
public:
    QJsonDocument Format(const ListEntity& list);
    QJsonDocument Format(const std::vector<ListEntity>& lists);
    QJsonDocument FormatId(const ListEntity& list);
};
