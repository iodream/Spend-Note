#pragma once

#include <string>
#include "Types.h"

struct Income
{
    idType id;
    idType userId;
    std::string name;
    double amount;
    idType categoryId;
    std::string addTime;
    std::string expoirationTime;
};
