#include "Utils.h"

#include "Logger/ScopedLogger.h"

db::Product ToDBProduct(const Product& product)
{
	SCOPED_LOGGER;
	db::Product db_product;
	db_product.id = product.id;
	db_product.list_id = product.list_id;
	db_product.category_id = product.category.id;
	db_product.name = product.name;
	db_product.price = product.price;
	db_product.amount = product.amount;
	db_product.product_priority = product.priority;
	db_product.is_bought = product.is_bought;
	db_product.add_date = product.add_date;
	db_product.add_date = product.add_date;
	db_product.purchase_date = (product.purchase_date != "")
			? std::optional<db::Timestamp>{product.purchase_date} : std::nullopt;
	db_product.buy_until_date = (product.buy_until_date != "")
			? std::optional<db::Timestamp>{product.buy_until_date} : std::nullopt;

	return db_product;
}
