#pragma once

#include "QJsonDocument"

#include "Net/Parsing.h"

template <template<typename> typename CategoryParser, typename PeriodicProduct>
class PeriodicProductJSONParserBase
{
	using ProductCategory = typename PeriodicProduct::CategoryType;
public:
	PeriodicProduct Parse(const QJsonObject& json)
	{
		PeriodicProduct product;
		QJsonObject category_json;
		CategoryParser<ProductCategory> category_parser;

		SafeReadId(json, "id", product.id);
		SafeReadId(json, "list_id", product.list_id);

		SafeReadObject(json, "category", category_json);
		product.category = category_parser.Parse(category_json);

		SafeReadString(json, "name", product.name);
		SafeReadBigInt(json, "amount", product.amount);
		SafeReadMoney(json, "price", product.price);
		SafeReadBigInt(json, "priority", product.priority);

		SafeReadString(json, "period_id", product.period_id);
		SafeReadString(json, "next_add_date", product.next_add_date);
		SafeReadString(json, "add_until", product.add_until);

		return product;
	}
};
