#pragma once

#include "Types.h"

struct ListEntity
{
    IdType id;
    std::string name;
    IdType owner_id;
    std::pair<IdType, std::string> state;
};
