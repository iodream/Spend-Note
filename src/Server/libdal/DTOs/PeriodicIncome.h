#pragma once

#include <string>
#include <optional>
#include "Types.h"

namespace db
{
	struct PeriodicIncome
	{
		IdType id;
		std::string name;
		IdType user_id;
		Money amount;
		IdType category_id;

		Timestamp next_add_date;
		std::optional<Timestamp> add_until;
		IdType period_id;
	};
}
