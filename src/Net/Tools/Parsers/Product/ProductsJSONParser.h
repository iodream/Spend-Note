#pragma once

#include "QJsonDocument"

#include "Net/Parsing.h"
#include "../../../Entities/Product.h"
#include "ProductJSONParser.h"

template <typename Entity>
class ProductsJSONParser
{
public:
	std::vector<Entity> Parse(const QJsonDocument& json_doc)
	{
		ProductJSONParser<Entity> product_parser;
		std::vector<Entity> products;
		QJsonArray json_array = json_doc.array();
		for (const auto& product_json : json_array)
		{
			products.push_back(product_parser.Parse(product_json));
		}
		return products;
	}
};
