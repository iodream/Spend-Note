#pragma once

#include "QJsonDocument"

#include "Net/Parsing.h"
#include "../../../Entities/Product.h"
#include "ProductCategoryJSONParser.h"

template <typename Entity>
class ProductJSONParser
{
	using ProductCategoryType = ProductCategory<typename Entity::StringType>;
public:
	Entity Parse(const QJsonDocument& json_doc)
	{
		Entity product;
		QJsonObject json = json_doc.object();
		QJsonObject category_json;
		ProductCategoryJSONParser<ProductCategoryType> category_parser;

		SafeReadId(json, "id", product.id);
		SafeReadId(json, "list_id", product.list_id);
		SafeReadObject(json, "category", category_json);
		product.category = category_parser.Parse(category_json);
		SafeReadBool(json, "is_bought", product.is_bought);
		SafeReadString(json, "name", product.name);
		SafeReadBigInt(json, "amount", product.amount);
		SafeReadMoney(json, "price", product.price);
		SafeReadBigInt(json, "priority", product.priority);
		SafeReadString(json, "add_date", product.add_date);
		SafeReadString(json, "purchase_date", product.purchase_date);
		SafeReadString(json, "buy_until_date", product.buy_until_date);

		return product;
	}
};
