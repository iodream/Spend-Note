#include "Utils.h"

#include "Net/Parsing.h"

Product ReassembleProduct(const QJsonObject& json)
{
	Product product;

	double tmp_number;
	std::string tmp_date;
	SafeReadId(json, "id", product.id);
	SafeReadId(json, "list_id", product.list_id);
	SafeReadId(json, "category_id", product.category_id);
	SafeReadString(json, "name", product.name);

	SafeReadNumber(json, "price", tmp_number);
	product.price = tmp_number;
	SafeReadNumber(json, "amount", tmp_number);
	product.amount = tmp_number;
	SafeReadNumber(json, "priority", tmp_number);
	product.product_priority = tmp_number;

	SafeReadBool(json, "is_bought", product.is_bought);
	SafeReadString(json, "add_date", product.add_date);

	SafeReadString(json, "purchase_date", tmp_date);
	product.purchase_date = (tmp_date != "")
		? std::optional<Timestamp>{tmp_date} : std::nullopt;
	SafeReadString(json, "buy_until_date", tmp_date);
	product.buy_until_date = (tmp_date != "")
		? std::optional<Timestamp>{tmp_date} : std::nullopt;

	return product;
}
