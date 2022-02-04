#pragma once

#include <string>
#include <optional>
#include "Types.h"

namespace db
{
	struct Product
	{
		IdType id;
		IdType list_id;
		IdType category_id;
		std::string name;
		Money price;
		BigInt amount;
		int product_priority;
		bool is_bought;
		Timestamp add_date;
		std::optional<Timestamp> purchase_date;
		std::optional<Timestamp> buy_until_date;
	};
}
