#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"

namespace
{

QJsonObject FormObject()
{
	QJsonObject object, tmp_object;

	object["id"] = 1;
	object["list_id"]  = 1;

	tmp_object["id"] = 1;
	tmp_object["name"] = "test_category";

	object["category"] = tmp_object;
	object["name"] = "test_name";
	object["is_bought"] = true;
	object["amount"] = 1;
	object["price"] = 100;
	object["priority"] = 1;
	object["add_date"] = "test_date";
	object["purchase_date"] = "test_date";
	object["buy_until_date"] = "test_date";

	return object;
}


Product FormProduct()
{
	Product product;

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

	return product;
}

void Testing(const QJsonObject& object, const QJsonObject& product)
{
	EXPECT_EQ(object["id"], product["id"]);
	EXPECT_EQ(object["list_id"], product["list_id"]);
	EXPECT_EQ(object["category"], product["category"]);
	EXPECT_EQ(object["is_bought"], product["is_bought"]);
	EXPECT_EQ(object["amount"], product["amount"]);
	EXPECT_EQ(object["price"], product["price"]);
	EXPECT_EQ(object["priority"], product["priority"]);
	EXPECT_EQ(object["add_date"], product["add_date"]);
	EXPECT_EQ(object["purchase_date"], product["purchase_date"]);
	EXPECT_EQ(object["buy_until_date"], product["buy_until_date"]);
}

}

TEST(ProductJSONFormatter, FORMAT)
{
	auto object = FormObject();
	ProductJSONFormatter m_formatter{};
	auto product = m_formatter.Format(FormProduct());

	Testing(object, product);
}
