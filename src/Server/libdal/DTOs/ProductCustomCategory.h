#pragma once

#include <string>
#include "Types.h"

namespace db
{
	struct ProductCustomCategory
	{
		IdType id;
		IdType user_id;
		std::string name;
	};
}
