#include "Utils.h"

#include "Logger/ScopedLogger.h"
#include "../Common.h"

db::PeriodicIncome ToDBPeriodicIncome(const PeriodicIncome& income, const IdType& user_id)
{
	SCOPED_LOGGER;
	db::PeriodicIncome db_income;
	db_income.id = income.id;
	db_income.user_id = user_id;
	db_income.name = income.name;
	db_income.amount = income.amount;
	db_income.category_id = income.category.id;
	db_income.period_id = income.period_id;
	db_income.next_add_date = income.next_add_date;
	db_income.add_until = (income.add_until != "")
			? std::optional<db::Timestamp>{income.add_until} : std::nullopt;

	return db_income;
}

PeriodicIncome ToNetPeriodicIncome(const db::PeriodicIncome& db_income, const db::IncomeCategory& category)
{
	SCOPED_LOGGER;
	PeriodicIncome income;
	income.id = db_income.id;
	income.name = db_income.name;
	income.category.id = category.id;
	income.category.name = category.name;
	income.amount = db_income.amount;
	income.period_id = db_income.period_id;
	income.next_add_date = db_income.next_add_date;
	income.add_until = (db_income.add_until.has_value()) ? db_income.add_until.value() : EMPTY_STD_STRING;

	return income;
}
