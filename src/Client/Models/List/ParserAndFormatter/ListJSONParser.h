#include <QJsonObject>

#include "ListEntity.h"
#include "../Net/Parsing.h"

class ListJSONParser
{
public:
    ListEntity Parse(const QJsonObject& obj);
};
