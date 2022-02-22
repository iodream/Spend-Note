#pragma once

#include "Types.h"

namespace db
{
	struct ExpensePerCategory
	{
		IdType category_id;
		Money amount;
	};

	struct ExpensePercentagePerCategory
	{
		IdType category_id;
		double percentage;
	};

	struct ExpensePerDay
	{
		Date day;
		Money amount;
	};
}
