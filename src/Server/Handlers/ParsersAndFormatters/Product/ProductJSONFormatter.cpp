#include <QJsonObject>

#include "../../Entities/ProductCategory.h"
#include "ProductCategoryJSONFormatter.h"
#include "Net/Parsing.h"
#include "ProductJSONFormatter.h"

QJsonDocument ProductJSONFormatter::FormatProduct(Product &product)
{
	ProductCategoryJSONFormatter category_formatter;
	QJsonObject json;
	ProductCategory category = product.category;
	WriteId(json, "id", product.id);
	WriteId(json, "list_id", product.list_id);
	json["category"] = category_formatter.FormatProductCategory(category).object();
	json["is_bought"] = product.is_bought;
	json["name"] = product.name.c_str();
	WriteBigInt(json, "amount", product.amount);
	WriteMoney(json, "price", product.price);
	json["priority"] = product.priority;
	json["add_date"] = product.add_date.c_str();
	json["purchase_date"] = product.purchase_date.c_str();
	json["buy_until_date"] = product.buy_until_date.c_str();

	return QJsonDocument{json};
}
