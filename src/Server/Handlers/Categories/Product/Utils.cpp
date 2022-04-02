#include "Utils.h"

#include "Logger/ScopedLogger.h"
#include "../../Common.h"

ProductCategory ToNetProductCategory(const db::ProductCategory& db_product_category)
{
	ProductCategory product_category;
	product_category.id = db_product_category.id;
	product_category.name = db_product_category.name;
	return product_category;
}

db::ProductCategory ToDBProductCategory(const ProductCategory& category, const IdType& user_id)
{
	db::ProductCategory db_category;
	db_category.id = category.id;
	db_category.name = category.name;
	db_category.user_id = user_id;
	return db_category;
}
