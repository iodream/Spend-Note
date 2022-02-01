#pragma once

#include <string>
#include "Types.h"

struct List
{
	IdType id;
	IdType owner_id;
	IdType state_id;
	std::string name;
};
