#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Server/Handlers/Categories/Income/GetIncomeCategoriesHandler.h"


using ::testing::Return;
using ::testing::_;

namespace  {

IncomeCategory category {
	1,
	"Category 1"
};

db::IncomeCategory db_category{
	1,
	1,
	"Category 1"
};

void CheckIncomeCategoryEquality(const IncomeCategory& category1, const IncomeCategory& category2)
{
	EXPECT_EQ(category1.id, category2.id);
	EXPECT_EQ(category1.name, category2.name);

}

std::unique_ptr<GetIncomeCategoriesHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetIncomeCategoriesHandler>();
	handler->set_facade(std::move(facade));

	return std::move(handler);
}

}

TEST(GetIncomeCategoriesHandlerTest, EMPTY_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomeCategories(1))
		.WillOnce(Return(std::vector<db::IncomeCategory>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray categories = response.json_payload.array();
	EXPECT_EQ(categories.size(), 0);
}

TEST(GetIncomeCategoriesHandlerTest, ONE_INCOME_CATEGORY)
{
	IncomeCategoryJSONParser m_parser;

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomeCategories(1))
		.WillOnce(Return(std::vector<db::IncomeCategory>{db_category}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray categories = response.json_payload.array();
	EXPECT_EQ(categories.size(), 1);

	auto category = m_parser.Parse(categories[0].toObject());

	CheckIncomeCategoryEquality(category, ::category);
}
