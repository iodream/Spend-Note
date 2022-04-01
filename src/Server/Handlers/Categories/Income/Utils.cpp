#include "Utils.h"

#include "Logger/ScopedLogger.h"
#include "../../Common.h"

IncomeCategory ToNetIncomeCategory(const db::IncomeCategory& db_income_category)
{
	IncomeCategory category;
	category.id = db_income_category.id;
	category.name = db_income_category.name;
	return category;
}

db::IncomeCategory ToDBIncomeCategory(const IncomeCategory& category, const IdType& user_id)
{
	db::IncomeCategory db_category;
	db_category.id = category.id;
	db_category.name = category.name;
	db_category.user_id = user_id;
	return db_category;
}
