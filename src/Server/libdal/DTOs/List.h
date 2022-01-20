#pragma once

#include <string>
#include "Types.h"

struct List
{
	IdType list_id;
	IdType owner_id;
	IdType state_id;
	std::string name;
};
