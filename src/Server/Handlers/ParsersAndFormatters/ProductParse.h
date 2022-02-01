#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <string>
#include <utility>

#include "../Entities/ProductCategory.h"
#include "../Entities/Product.h"
#include "ProductCategoryParse.h"
#include "Net/Parsing.h"
#include "../Handlers/Common.h"

Product ProductParse(QJsonObject& json)
{
	Product product;
	double tmp_number;
	QJsonObject json_for_category;

	SafeReadId(json, "id", product.id);
	SafeReadId(json, "list_id", product.list_id);
	SafeReadObject(json, "category", json_for_category);
	product.category = ProductCategoryParse(json_for_category);
	SafeReadBool(json, "is_bought", product.is_bought);
	SafeReadString(json, "name", product.name);
	SafeReadAmount(json, "amount", product.amount);
	SafeReadPrice(json, "price", product.price);
	SafeReadNumber(json, "priority", tmp_number);
	product.priority = tmp_number;
	SafeReadString(json, "add_date", product.add_date);
	SafeReadString(json, "purchase_date", product.purchase_date);
	SafeReadString(json, "buy_until_date", product.buy_until_date);

	return product;
}
