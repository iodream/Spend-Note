#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <string>

#include "../Entities/Product.h"
#include "../Entities/ProductCategory.h"
#include "ProductCategoryFormat.h"
#include "Net/Parsing.h"
#include "../Handlers/Common.h"

QJsonDocument GetProductsFormatter(Product& product)
{
	QJsonObject json;
	ProductCategory category = product.category;
	SafeWriteId(json, "id", product.id);
	SafeWriteId(json, "list_id", product.list_id);
	json["category"] = ProductCategoryFormatter(category);
	json["is_bought"] = product.is_bought;
	json["name"] = product.name.c_str();
	SafeWriteAmount(json, "amount", product.amount);
	SafeWritePrice(json, "price", product.price);
	json["priority"] = product.priority;
	json["add_date"] = product.add_date.c_str();
	json["purchase_date"] = product.purchase_date.c_str();
	json["buy_until_date"] = product.buy_until_date.c_str();

	return QJsonDocument{json};
}
