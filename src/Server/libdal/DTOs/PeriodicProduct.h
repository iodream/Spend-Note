#pragma once

#include <string>
#include <optional>
#include "Types.h"

namespace db
{
	struct PeriodicProduct
	{
		IdType id;
		IdType list_id;
		IdType category_id;
		std::string name;
		Money price;
		BigInt amount;
		int product_priority;
		Timestamp next_add_date;
		std::optional<Timestamp> add_until;
		IdType period_id;
	};
}
