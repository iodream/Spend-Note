#pragma once

#include "QJsonDocument"
#include "QJsonArray"
#include "vector"

#include "Net/Parsing.h"
#include "../../../Entities/Product.h"
#include "ProductJSONFormatter.h"

template <typename Entity>
class ProductsJSONFormatter
{
public:
	QJsonDocument Format(const std::vector<Entity>& products)
	{
		ProductJSONFormatter<Entity> product_formatter;
		QJsonArray json_array;
		for (const auto& product : products)
		{
			QJsonObject product_json = product_formatter.Format(product).object();
			json_array.append(product_json);
		}
		return QJsonDocument{json_array};
	}
};
