#pragma once

#include "Types.h"
#include <QString>

struct ListEntity
{
    IdType id;
    QString name;
    IdType owner_id;
    std::pair<IdType, QString> state;
};
