#pragma once

#include "Types.h"
#include "ListState.h"

template<typename T>
struct ListEntity
{
    IdType id;
    T name;
    IdType owner_id;
    ListStatetEntity<T> state;
};
