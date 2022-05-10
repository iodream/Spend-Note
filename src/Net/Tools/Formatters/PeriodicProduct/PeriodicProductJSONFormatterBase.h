#pragma once

#include <QJsonDocument>

#include "Net/Parsing.h"

template <template<typename> typename CategoryFormatter, typename Product>
class PeriodicProductJSONFormatterBase
{
	using ProductCategory = typename Product::CategoryType;
public:
	QJsonObject Format(const PeriodicProduct& product)
	{
		CategoryFormatter<ProductCategory> category_formatter;
		QJsonObject json;
		auto category = product.category;
		WriteId(json, "id", product.id);
		WriteId(json, "list_id", product.list_id);

		json["category"] = category_formatter.Format(category);

		WriteString(json, "name", product.name);
		WriteBigInt(json, "amount", product.amount);
		WriteMoney(json, "price", product.price);
		WriteBigInt(json, "priority", product.priority);

		WriteId(json, "period_id", product.period_id);
		WriteString(json, "next_add_date", product.next_add_date);
		WriteString(json, "add_until", product.add_until);

		return json;
	}
};
