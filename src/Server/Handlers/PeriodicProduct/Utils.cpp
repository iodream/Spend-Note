#include "Utils.h"

#include "Logger/ScopedLogger.h"
#include "../Common.h"

db::PeriodicProduct ToDBPeriodicProduct(const PeriodicProduct& product)
{
	SCOPED_LOGGER;
	db::PeriodicProduct db_product;
	db_product.id = product.id;
	db_product.list_id = product.list_id;
	db_product.category_id = product.category.id;
	db_product.name = product.name;
	db_product.price = product.price;
	db_product.amount = product.amount;
	db_product.product_priority = product.priority;
	db_product.period_id = product.period_id;
	db_product.next_add_date = product.next_add_date;
	db_product.add_until = (product.add_until != "")
			? std::optional<db::Timestamp>{product.add_until} : std::nullopt;

	return db_product;
}

PeriodicProduct ToNetPeriodicProduct(const db::PeriodicProduct& db_product, const db::ProductCategory& category)
{
	SCOPED_LOGGER;
	PeriodicProduct product;
	product.id = db_product.id;
	product.list_id = db_product.list_id;
	product.name = db_product.name;
	product.category.id = category.id;
	product.category.name = category.name;
	product.price = db_product.price;
	product.amount = db_product.amount;
	product.priority = db_product.product_priority;
	product.period_id = db_product.period_id;
	product.next_add_date = db_product.next_add_date;
	product.add_until = (db_product.add_until.has_value()) ? db_product.add_until.value() : EMPTY_STD_STRING;

	return product;
}
