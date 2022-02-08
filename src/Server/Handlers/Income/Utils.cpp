#include "Utils.h"

#include "Logger/ScopedLogger.h"

db::Income ToDBIncome(const Income& income)
{
	SCOPED_LOGGER;
	db::Income db_income;
	db_income.id = income.id;
	db_income.user_id = income.user_id;
	db_income.name = income.name;
	db_income.amount = income.amount;
	db_income.category_id = income.category.id;
	db_income.add_time = income.add_time;
	db_income.expiration_time = (income.expiration_time != "")
		? std::optional<db::Timestamp>{income.expiration_time} : std::nullopt;

	return db_income;
}

