#include "Utils.h"
Product ParseProduct(const QJsonObject& json)
{
	double tmp_number;
	Product product;

	SafeReadId(json, "id", product.id);
	SafeReadId(json, "list_id", product.list_id);
	SafeReadId(json, "category_id", product.category_id);
	SafeReadQString(json, "name", product.name);
	SafeReadNumber(json, "price", product.price);
	SafeReadId(json, "amount", product.amount);

	SafeReadNumber(json, "product_priority", tmp_number);
	product.product_priority = tmp_number;

	SafeReadBool(json, "is_bought", product.is_bought);
	SafeReadQString(json, "add_date", product.add_date);
	SafeReadQString(json, "purchase_date", product.purchase_date);
	SafeReadQString(json, "buy_until_date", product.buy_until_date);

	return product;
}

QJsonDocument FormatProduct(const Product& product)
{
	QJsonObject json;

	json["id"] = std::to_string(product.id).c_str();
	json["list_id"] = std::to_string(product.list_id).c_str();
	json["category_id"] = std::to_string(product.category_id).c_str();
	json["name"] = product.name.toStdString().c_str();
	json["price"] = product.price;
	json["amount"] = std::to_string(product.amount).c_str();
	json["product_priority"] = std::to_string(product.product_priority).c_str();
	json["is_bought"] = product.is_bought;
	json["add_date"] = product.add_date.toStdString().c_str();
	json["purchase_date"] = product.purchase_date.toStdString().c_str();
	json["buy_until_date"] = product.buy_until_date.toStdString().c_str();

	return QJsonDocument{json};
}
