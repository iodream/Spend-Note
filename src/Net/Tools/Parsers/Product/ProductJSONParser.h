#pragma once

#include "QJsonDocument"

#include "Net/Parsing.h"
#include "../../../Entities/Product.h"
#include "ProductCategoryJSONParser.h"

template <typename T>
class ProductJSONParser
{
	using ProductCategoryType = ProductCategory<typename T::StringType>;
public:
	T Parse(const QJsonObject& json)
	{
		T product;
		double tmp_number;
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
		SafeReadNumber(json, "priority", tmp_number);
		product.priority = tmp_number;
		SafeReadString(json, "add_date", product.add_date);
		SafeReadString(json, "purchase_date", product.purchase_date);
		SafeReadString(json, "buy_until_date", product.buy_until_date);

		return product;
	}
};
