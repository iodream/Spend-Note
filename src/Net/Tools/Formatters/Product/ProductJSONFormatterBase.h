#pragma once

#include <QJsonDocument>

#include "Net/Parsing.h"

template <template<typename> typename CategoryFormatter, typename Product>
class ProductJSONFormatterBase
{
	using ProductCategory = typename Product::CategoryType;
public:
	QJsonObject Format(const Product& product)
	{
		CategoryFormatter<ProductCategory> category_formatter;
		QJsonObject json;
		auto category = product.category;
		WriteId(json, "id", product.id);
		WriteId(json, "list_id", product.list_id);

		json["category"] = category_formatter.FormatProductCategory(category);

		json["is_bought"] = product.is_bought;
		WriteString(json, "name", product.name);
		WriteBigInt(json, "amount", product.amount);
		WriteMoney(json, "price", product.price);
		WriteBigInt(json, "priority", product.priority);

		WriteString(json, "add_date", product.add_date);
		WriteString(json, "purchase_date", product.purchase_date);
		WriteString(json, "buy_until_date", product.buy_until_date);

		return json;
	}
};
