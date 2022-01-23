#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Product/GetProductsHandler.h"
#include "Server/Handlers/Product/Utils.h"
#include "Net/Parsing.h"


using ::testing::Return;
using ::testing::_;

namespace  {

Product p1 {
	1,
	1,
	1,
	"Product 1",
	123,
	123,
	0,
	false,
	"some_date",
	std::optional<Timestamp>{},
	std::optional<Timestamp>{}
};

ProductCategory c1 {
	1,
	"Category 1"
};

void CheckProductsEquality(const Product& p1, const Product& p2)
{
	EXPECT_EQ(p1.id, p2.id);
	EXPECT_EQ(p1.list_id, p2.list_id);
	EXPECT_EQ(p1.category_id, p2.category_id);
	EXPECT_EQ(p1.name, p2.name);
	EXPECT_EQ(p1.price, p2.price);
	EXPECT_EQ(p1.amount, p2.amount);
	EXPECT_EQ(p1.product_priority, p2.product_priority);
	EXPECT_EQ(p1.is_bought, p2.is_bought);
	EXPECT_EQ(p1.add_date, p2.add_date);
	EXPECT_EQ(p1.purchase_date, p2.purchase_date);
	EXPECT_EQ(p1.buy_until_date, p2.buy_until_date);
}

}

TEST(GetProductsHandlerTest, EMPTY_PRODUCTS_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetProductsForList(_))
		.WillOnce(Return(std::vector<Product>{}));

	auto handler = std::make_unique<GetProductsHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["list_id"] = "1";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonObject json = response.json_payload.object();
	QJsonArray products;
	SafeReadArray(json, "products", products);
	EXPECT_EQ(products.size(), 0);
}

TEST(GetProductsHandlerTest, ONE_PRODUCT_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetProductsForList(_))
		.WillOnce(Return(std::vector<Product>{p1}));
	EXPECT_CALL(*facade, GetProductCategoryById(1))
		.WillOnce(Return(std::optional<ProductCategory>{c1}));

	auto handler = std::make_unique<GetProductsHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["list_id"] = "1";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonObject json = response.json_payload.object();
	QJsonArray products;
	SafeReadArray(json, "products", products);
	EXPECT_EQ(products.size(), 1);

	auto product = products.at(0).toObject();
	auto product_dto = ParseProduct(product);

	CheckProductsEquality(p1, product_dto);

	EXPECT_EQ(c1.id, product_dto.category_id);
	EXPECT_EQ(c1.name, product["category"].toString().toStdString());
}
