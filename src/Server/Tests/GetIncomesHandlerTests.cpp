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
		.WillOnce(Return(std::vector<db::Income>{}));

	auto handler = std::make_unique<GetIncomesHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));

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
	db::Income i;
	i.id = 1;
	i.user_id = 1;
	i.name = "Test income";
	i.amount = 100;
	i.category_id = 1;
	i.add_time = "2022-01-23 20:00:00";
	i.expiration_time = "2022-01-30 20:00:00";

	db::IncomeCategory c;
	c.id = 1;
	c.name = "Test category";

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomes(_))
		.WillOnce(Return(std::vector<db::Income>{i}));
	EXPECT_CALL(*facade, GetIncomeCategoryById(1))
		.WillOnce(Return(std::optional<db::IncomeCategory>{c}));

	auto handler = std::make_unique<GetIncomesHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonObject json = response.json_payload.object();
	QJsonArray incomes;
	SafeReadArray(json, "incomes", incomes);
	EXPECT_EQ(incomes.size(), 1);

	auto income_json = incomes[0].toObject();
	ASSERT_EQ(income_json["id"].toString(), QString::number(i.id));
	ASSERT_EQ(income_json["user_id"].toString(), QString::number(i.user_id));
	ASSERT_EQ(income_json["name"].toString(), QString::fromStdString(i.name));
	ASSERT_EQ(income_json["amount"].toDouble(), i.amount);
	ASSERT_EQ(income_json["category_name"].toString(), QString::fromStdString(c.name));
	ASSERT_EQ(income_json["add_time"].toString(), QString::fromStdString(i.add_time));
	ASSERT_EQ(income_json["expiration_time"].toString(), QString::fromStdString(i.expiration_time.value_or("")));
}

TEST(GetIncomesHandlerTest, SQL_FAILURE)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomes(_))
		.WillOnce(Throw(db::SQLFailure("")));

	auto handler = std::make_unique<GetIncomesHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
}
