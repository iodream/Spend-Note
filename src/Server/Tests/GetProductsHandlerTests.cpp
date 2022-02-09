#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Product/GetProductsHandler.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Net/Parsing.h"


using ::testing::Return;
using ::testing::_;

namespace  {

db::Product p1 {
	1,
	1,
	1,
	"Product 1",
	123,
	123,
	0,
	false,
	"some_date",
	std::optional<db::Timestamp>{},
	std::optional<db::Timestamp>{}
};

db::ProductCategory c1 {
	1,
	"Category 1"
};

void CheckProductsEquality(const db::Product& p1, const Product& p2)
{
	EXPECT_EQ(p1.id, p2.id);
	EXPECT_EQ(p1.list_id, p2.list_id);
	EXPECT_EQ(p1.category_id, p2.category.id);
	EXPECT_EQ(p1.name, p2.name);
	EXPECT_EQ(p1.price, p2.price);
	EXPECT_EQ(p1.amount, p2.amount);
	EXPECT_EQ(p1.product_priority, p2.priority);
	EXPECT_EQ(p1.is_bought, p2.is_bought);
	EXPECT_EQ(p1.add_date, p2.add_date);
	EXPECT_EQ(p1.purchase_date, p2.purchase_date);
	EXPECT_EQ(p1.buy_until_date, p2.buy_until_date);
}

std::unique_ptr<GetProductsHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetProductsHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::LIST_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}

TEST(GetProductsHandlerTest, EMPTY_PRODUCTS_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetProductsForList(_))
		.WillOnce(Return(std::vector<db::Product>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	ProductsJSONParser m_parser;
	auto procucts = m_parser.Parse(request.json_payload.array());
	EXPECT_EQ(procucts.size(), 0);
}

TEST(GetProductsHandlerTest, ONE_PRODUCT_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	auto vect = std::vector<db::Product>{p1};
	EXPECT_CALL(*facade, GetProductsForList(_))
		.WillOnce(Return(vect));
	//EXPECT_CALL(*facade, GetProductCategoryById(1))
		//.WillOnce(Return(std::optional<db::ProductCategory>{c1}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	{
	ProductsJSONParser m_parser;
	auto procucts = m_parser.Parse(request.json_payload.array());
	ASSERT_EQ(procucts.size(), 1);

	CheckProductsEquality(p1, procucts.at(0));

	EXPECT_EQ(c1.id, procucts.at(0).category.id);
	EXPECT_EQ(c1.name, procucts.at(0).category.name);
	}
}

