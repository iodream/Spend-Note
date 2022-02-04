#pragma once

#include "QJsonDocument"

#include "Net/Parsing.h"

template <template<typename> typename CategoryParser, typename Product>
class ProductJSONParserBase
{
	using ProductCategory = typename Product::CategoryType;
public:
	Product Parse(const QJsonObject& json)
	{
		Product product;
		QJsonObject category_json;
		CategoryParser<ProductCategory> category_parser;

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
