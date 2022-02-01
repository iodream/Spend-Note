#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <string>
#include <utility>

#include "../Entities/ProductCategory.h"
#include "../Entities/Product.h"
#include "ProductCategoryParser.h"
#include "Net/Parsing.h"
#include "../Handlers/Common.h"

Product ProductParser(QJsonObject& json)
{
	Product product;
	double tmp_number;
	ProductCategory category;
	QJsonObject json_for_category;

	SafeReadId(json, "id", product.id);
	SafeReadId(json, "list_id", product.list_id);
	SafeReadObject(json, "category", json_for_category);
	product.category = ProductCategoryParser(json_for_category);
	SafeReadBool(json, "is_bought", product.is_bought);
	SafeReadString(json, "name", product.name);
	SafeReadId(json, "amount", product.amount);
	SafeReadId(json, "price", product.price);
	SafeReadNumber(json, "priority", tmp_number);
	product.priority = tmp_number;
	SafeReadString(json, "add_date", product.add_date);
	SafeReadString(json, "purchase_date", product.purchase_date);
	SafeReadString(json, "buy_until_date", product.buy_until_date);

	return product;
}
