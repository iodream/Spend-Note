#include <QJsonObject>

#include "ProductCategoryJSONParser.h"
#include "Net/Parsing.h"
#include "ProductJSONParser.h"

Product ProductJSONParser::ParseProduct(const QJsonObject &json)
{
	Product product;
	double tmp_number;
	QJsonObject category_json;
	ProductCategoryJSONParser category_parser;

	SafeReadId(json, "id", product.id);
	SafeReadId(json, "list_id", product.list_id);
	SafeReadObject(json, "category", category_json);
	product.category = category_parser.ParseProductCategory(category_json);
	SafeReadBool(json, "is_bought", product.is_bought);
	SafeReadQString(json, "name", product.name);
	SafeReadBigInt(json, "amount", product.amount);
	SafeReadMoney(json, "price", product.price);
	SafeReadNumber(json, "priority", tmp_number);
	product.priority = tmp_number;
	SafeReadQString(json, "add_date", product.add_date);
	SafeReadQString(json, "purchase_date", product.purchase_date);
	SafeReadQString(json, "buy_until_date", product.buy_until_date);

	return product;
}
