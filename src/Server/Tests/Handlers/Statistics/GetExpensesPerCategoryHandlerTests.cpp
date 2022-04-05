#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Server/Handlers/Statistics/GetExpensesPerCategoryHandler.h"
#include "Net/Parsing.h"


using ::testing::Return;
using ::testing::_;

namespace  {

db::ExpensePerCategory db_expense{
	1,
	1
};

StatisticPerCategory expense{
	1,
	1
};

std::unique_ptr<GetExpensesPerCategoryHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetExpensesPerCategoryHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}


TEST(GetExpensesPerCategoryHandlerTest, EMPTY_EXPENSES)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, ExpensesPerCategory(1, db::Period::Weekly))
		.WillOnce(Return(std::vector<db::ExpensePerCategory>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray lists = response.json_payload.array();
	EXPECT_EQ(lists.size(), 0);
}

TEST(GetExpensesPerCategoryHandlerTest, FORBIDDEN)
{
	auto facade = std::make_unique<MockDbFacade>();
	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 2;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_FORBIDDEN);
}

TEST(GetExpensesPerCategoryHandlerTest, ONE_EXPENSE)
{
	StatisticPerCategoryJSONParser m_parser;
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, ExpensesPerCategory(1, db::Period::Weekly))
		.WillOnce(Return(std::vector<db::ExpensePerCategory>{db_expense}));

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
	EXPECT_EQ(expense.amount, ::expense.amount);
}
