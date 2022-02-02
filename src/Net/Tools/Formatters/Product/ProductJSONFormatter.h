#pragma once

#include "QJsonDocument"

#include "Net/Parsing.h"
#include "../../../Entities/Product.h"
#include "ProductCategoryJSONFormatter.h"

template <typename Entity>
class ProductJSONFormatter
{
	using ProductCategoryType = ProductCategory<typename Entity::StringType>;
public:
	QJsonDocument Format(const Entity& product)
	{
		ProductCategoryJSONFormatter<ProductCategoryType> category_formatter;
		QJsonObject json;
		auto category = product.category;
		WriteId(json, "id", product.id);
		WriteId(json, "list_id", product.list_id);
		json["category"] = category_formatter.FormatProductCategory(category).object();
		json["is_bought"] = product.is_bought;
		WriteString(json, "name", product.name);
		WriteBigInt(json, "amount", product.amount);
		WriteMoney(json, "price", product.price);
		WriteBigInt(json, "priority", product.priority);
		WriteString(json, "add_date", product.add_date);
		WriteString(json, "purchase_date", product.purchase_date);
		WriteString(json, "buy_until_date", product.buy_until_date);

		return QJsonDocument{json};
	}
};
