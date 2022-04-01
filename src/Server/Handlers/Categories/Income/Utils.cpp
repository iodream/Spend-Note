#include "Utils.h"

#include "../../Common.h"

db::IncomeCategory ToDBIncomeCategory(const IncomeCategory& category, const IdType user_id)
{
	db::IncomeCategory db_category;
	db_category.user_id = user_id;
	db_category.name = category.name;
	db_category.id = category.id;
	return db_category;
}

//IncomeCategory ToNetIncomeCategory(const db::IncomeCategory& db_category)
//{
//	IncomeCategory category;
//	category.id	= db_category.id;
//	category.name = db_category.name;
//	return category;
//}
