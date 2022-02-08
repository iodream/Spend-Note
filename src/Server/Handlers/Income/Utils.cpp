#include "Utils.h"

#include "Logger/ScopedLogger.h"
#include "../Common.h"

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

Income ToNetIncome(const db::Income &db_income, const db::IncomeCategory& category)
{
	SCOPED_LOGGER;
	Income income;
	income.id = db_income.id;
	income.user_id = db_income.id;
	income.name = db_income.name;
	income.category.id = category.id;
	income.category.name = category.name;
	income.amount = db_income.amount;
	income.add_time = db_income.add_time;
	income.expiration_time = (db_income.expiration_time.has_value()) ? db_income.expiration_time.value() : EMPTY_STD_STRING;

	return income;
}
