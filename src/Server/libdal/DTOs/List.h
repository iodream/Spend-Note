#pragma once

#include <string>
#include "Types.h"

namespace db
{
	struct List
	{
		IdType id;
		IdType owner_id;
		IdType state_id;
		std::string name;
	};
}
