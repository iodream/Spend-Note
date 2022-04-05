#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Server/Handlers/Statistics/GetExpensesPercentagePerCategoryHandler.h"
#include "Net/Parsing.h"


using ::testing::Return;
using ::testing::_;

namespace  {

db::ExpensePercentagePerCategory db_expense{
	1,
	1
};

StatisticPercentagePerCategory expense{
	1,
	1
};

std::unique_ptr<GetExpensesPercentagePerCategoryHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetExpensesPercentagePerCategoryHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}


TEST(GetExpensesPercentagePerCategoryHandlerTest, EMPTY_EXPENSES)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, ExpensesPercentagePerCategory(1, db::Period::Weekly))
		.WillOnce(Return(std::vector<db::ExpensePercentagePerCategory>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray lists = response.json_payload.array();
	EXPECT_EQ(lists.size(), 0);
}

TEST(GetExpensesPercentagePerCategoryHandlerTest, FORBIDDEN)
{
	auto facade = std::make_unique<MockDbFacade>();
	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 2;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_FORBIDDEN);
}

TEST(GetExpensesPercentagePerCategoryHandlerTest, ONE_EXPENSE)
{
	StatisticPercentagePerCategoryJSONParser m_parser;
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, ExpensesPercentagePerCategory(1, db::Period::Weekly))
		.WillOnce(Return(std::vector<db::ExpensePercentagePerCategory>{db_expense}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray lists = response.json_payload.array();
	EXPECT_EQ(lists.size(), 1);

	auto expense = m_parser.Parse(lists[0].toObject());

	EXPECT_EQ(expense.category_id, ::expense.category_id);
	EXPECT_EQ(expense.percentage, ::expense.percentage);
}
