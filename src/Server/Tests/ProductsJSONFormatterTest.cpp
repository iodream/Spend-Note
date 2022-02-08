#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"

namespace
{

QJsonArray FormObjects()
{
	QJsonObject object, tmp_object;

	object["id"] = 1;
	object["list_id"]  = 1;

	tmp_object["id"] = 1;
	tmp_object["name"] = "test_category";

	object["category"] = tmp_object;
	object["is_bought"] = true;
	object["amount"] = 1;
	object["price"] = 100;
	object["priority"] = 1;
	object["add_date"] = "test_date";
	object["purchase_date"] = "test_date";
	object["buy_until_date"] = "test_date";

	return QJsonArray{object};
}


std::vector<Product> FormProduct()
{
	Product product;
	std::vector<Product> vect;

	product.id = 1;
	product.list_id = 1;
	product.category.id = 1;
	product.category.name = "test_category";
	product.is_bought = true;
	product.name = "test_name";
	product.amount = 1;
	product.price = 100;
	product.priority = 1;
	product.add_date = "test_date";
	product.purchase_date = "test_date";
	product.buy_until_date = "test_date";

	vect.push_back(product);
	return vect;
}

}

TEST(ProductsJSONFormatter, FORMATTER)
{
	auto objects = FormObjects();
	ProductsJSONFormatter m_formatter{};
	auto products = m_formatter.Format(FormProduct());

	QJsonObject product_obj1, product_obj2;

	for(const QJsonValue& el : products)
	{
		product_obj1 = el.toObject();
	}
	for(const QJsonValue& el : objects)
	{
		product_obj2 = el.toObject();
	}

	EXPECT_EQ(product_obj1["id"], product_obj2["id"]);
	EXPECT_EQ(product_obj1["list_id"], product_obj2["list_id"]);
	EXPECT_EQ(product_obj1["category"], product_obj2["category"]);
	EXPECT_EQ(product_obj1["is_bought"], product_obj2["is_bought"]);
	EXPECT_EQ(product_obj1["amount"], product_obj2["amount"]);
	EXPECT_EQ(product_obj1["price"], product_obj2["price"]);
	EXPECT_EQ(product_obj1["priority"], product_obj2["priority"]);
	EXPECT_EQ(product_obj1["add_date"], product_obj2["add_date"]);
	EXPECT_EQ(product_obj1["purchase_date"], product_obj2["purchase_date"]);
	EXPECT_EQ(product_obj1["buy_until_date"], product_obj2["buy_until_date"]);
}
