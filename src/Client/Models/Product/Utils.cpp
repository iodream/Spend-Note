#include "Utils.h"

ProductCategory ParseProductCategory(const QJsonObject& json)
{
	ProductCategory category;
	SafeReadId(json, "id", category.id);
	SafeReadQString(json, "name", category.name);
	return category;
}

QJsonDocument FormatProductCategory(ProductCategory& category)
{
	QJsonObject json;
	json["name"] = category.name.toStdString().c_str();
	SafeWriteId(json, "id", category.id);
	return QJsonDocument{json};
}

ProductId ParseProductId(const QJsonObject& json)
{
	ProductId product_id;
	SafeReadId(json, "id", product_id.id);
	return product_id;
}

QJsonDocument FormatProductId(ProductId& product_id)
{
	QJsonObject json;
	SafeWriteId(json, "id", product_id.id);
	return QJsonDocument{json};
}

Product ParseProduct(const QJsonObject& json)
{
	Product product;
	double tmp_number;
	QJsonObject json_for_category;

	SafeReadId(json, "id", product.id);
	SafeReadId(json, "list_id", product.list_id);
	SafeReadObject(json, "category", json_for_category);
	product.category = ParseProductCategory(json_for_category);
	SafeReadBool(json, "is_bought", product.is_bought);
	SafeReadQString(json, "name", product.name);
	SafeReadAmount(json, "amount", product.amount);
	SafeReadPrice(json, "price", product.price);
	SafeReadNumber(json, "priority", tmp_number);
	product.priority = tmp_number;
	SafeReadQString(json, "add_date", product.add_date);
	SafeReadQString(json, "purchase_date", product.purchase_date);
	SafeReadQString(json, "buy_until_date", product.buy_until_date);

	return product;
}

QJsonDocument FormatProduct(Product& product)
{
	QJsonObject json;
	ProductCategory category = product.category;
	SafeWriteId(json, "id", product.id);
	SafeWriteId(json, "list_id", product.list_id);
	json["category"] = FormatProductCategory(category).object();
	json["is_bought"] = product.is_bought;
	json["name"] = product.name.toStdString().c_str();
	SafeWriteAmount(json, "amount", product.amount);
	SafeWritePrice(json, "price", product.price);
	json["priority"] = product.priority;
	json["add_date"] = product.add_date.toStdString().c_str();
	json["purchase_date"] = product.purchase_date.toStdString().c_str();
	json["buy_until_date"] = product.buy_until_date.toStdString().c_str();

	return QJsonDocument{json};
}

