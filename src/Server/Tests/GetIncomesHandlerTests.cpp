#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Income/GetIncomesHandler.h"
#include "Net/Parsing.h"
#include "../libdal/Exceptions/SQLFailure.h"


using ::testing::Return;
using ::testing::_;
using ::testing::Throw;

TEST(GetIncomesHandlerTest, EMPTY_INCOME_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomes(_))
		.WillOnce(Return(std::vector<Income>{}));

	auto handler = std::make_unique<GetIncomesHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonObject json = response.json_payload.object();
	QJsonArray incomes;
	SafeReadArray(json, "incomes", incomes);
	EXPECT_EQ(incomes.size(), 0);
}

TEST(GetIncomesHandlerTest, ONE_INCOME_LIST)
{
	Income income;
	income.income_id = 1;
	income.user_id = 1;
	income.name = "Test income";
	income.amount = 100;
	income.category_id = 1;
	income.add_time = "2022-01-23 20:00:00";
	income.expiration_time = "2022-01-30 20:00:00";

	IncomeCategory category;
	category.income_category_id = 1;
	category.name = "Test category";

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomes(_))
		.WillOnce(Return(std::vector<Income>{income}));
	EXPECT_CALL(*facade, GetIncomeCategoryById(1))
		.WillOnce(Return(std::optional<IncomeCategory>{category}));

	auto handler = std::make_unique<GetIncomesHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonObject json = response.json_payload.object();
	QJsonArray incomes;
	SafeReadArray(json, "incomes", incomes);
	EXPECT_EQ(incomes.size(), 1);

	auto income_json = incomes[0].toObject();
	ASSERT_EQ(income_json["id"].toString(), QString::number(income.income_id));
	ASSERT_EQ(income_json["user_id"].toString(), QString::number(income.user_id));
	ASSERT_EQ(income_json["name"].toString(), QString::fromStdString(income.name));
	ASSERT_EQ(income_json["amount"].toDouble(), income.amount);
	ASSERT_EQ(income_json["category_name"].toString(), QString::fromStdString(category.name));
	ASSERT_EQ(income_json["add_time"].toString(), QString::fromStdString(income.add_time));
	ASSERT_EQ(income_json["expiration_time"].toString(), QString::fromStdString(income.expiration_time.value_or("")));
}

TEST(GetIncomesHandlerTest, SQL_FAILURE)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomes(_))
		.WillOnce(Throw(SQLFailure("")));

	auto handler = std::make_unique<GetIncomesHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
}
