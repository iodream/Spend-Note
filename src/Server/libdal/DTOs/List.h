#pragma once

#include <string>
#include "Types.h"

struct List
{
    idType id;
    idType ownerId;
    idType stateId;
    std::string name;
};
