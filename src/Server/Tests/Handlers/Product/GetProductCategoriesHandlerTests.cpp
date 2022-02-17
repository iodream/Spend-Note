#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Server/Handlers/Product/GetProductCategoriesHandler.h"


using ::testing::Return;
using ::testing::_;

namespace  {

ProductCategory category {
	1,
	"Category 1"
};

db::ProductCategory db_category{
	1,
	"Category 1"
};

void CheckProductCategoryEquality(const ProductCategory& category1, const ProductCategory& category2)
{
	EXPECT_EQ(category1.id, category2.id);
	EXPECT_EQ(category1.name, category2.name);

}

std::unique_ptr<GetProductCategoriesHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetProductCategoriesHandler>();
	handler->set_facade(std::move(facade));

	return std::move(handler);
}

}

TEST(GetProductCategoriesHandlerTest, EMPTY_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllProductCategories())
		.WillOnce(Return(std::vector<db::ProductCategory>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray categories = response.json_payload.array();
	EXPECT_EQ(categories.size(), 0);
}

TEST(GetProductCategoriesHandlerTest, ONE_PRODUCT_CATEGORY)
{
	ProductCategoryJSONParser m_parser;

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllProductCategories())
		.WillOnce(Return(std::vector<db::ProductCategory>{db_category}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray categories = response.json_payload.array();
	EXPECT_EQ(categories.size(), 1);

	auto category = m_parser.Parse(categories[0].toObject());

	CheckProductCategoryEquality(category, ::category);
}
