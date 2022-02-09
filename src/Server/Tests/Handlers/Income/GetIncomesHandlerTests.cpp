#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/Income/GetIncomesHandler.h"
#include "Net/Parsing.h"
#include "../libdal/Exceptions/SQLFailure.h"


using ::testing::Return;
using ::testing::_;
using ::testing::Throw;

namespace  {

db::Income CreateIncome()
{
	db::Income income;
	income.id = 1;
	income.name = "Test income";
	income.amount = 100;
	income.category_id = 1;
	income.add_time = "2022-01-23 20:00:00";
	income.expiration_time = "2022-01-30 20:00:00";
	return income;
}

db::IncomeCategory CreateIncomeCategory()
{
	db::IncomeCategory category;
	category.id = 1;
	category.name = "Test category";
	return category;
}

std::unique_ptr<GetIncomesHandler> CreateHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetIncomesHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}

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

	QJsonArray array = response.json_payload.array();
	EXPECT_EQ(array.size(), 0);
}

TEST(GetIncomesHandlerTest, ONE_INCOME_LIST)
{
	db::Income income = CreateIncome();
	db::IncomeCategory category = CreateIncomeCategory();

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllIncomes(_))
		.WillOnce(Return(std::vector<db::Income>{income}));
	EXPECT_CALL(*facade, GetIncomeCategoryById(1))
		.WillOnce(Return(std::optional<db::IncomeCategory>{category}));

	auto handler = CreateHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray array= response.json_payload.array();
	EXPECT_EQ(array.size(), 1);

	auto income_json = array[0].toObject();
	auto category_json = income_json["category"].toObject();
	ASSERT_EQ(income_json["id"], income.id);
	ASSERT_EQ(income_json["name"].toString(), QString::fromStdString(income.name));
	ASSERT_EQ(income_json["amount"].toDouble(), income.amount);
	ASSERT_EQ(category_json["id"], category.id);
	ASSERT_EQ(category_json["name"].toString(), QString::fromStdString(category.name));
	ASSERT_EQ(income_json["add_time"].toString(), QString::fromStdString(income.add_time));
	ASSERT_EQ(income_json["expiration_time"].toString(), QString::fromStdString(income.expiration_time.value_or("")));
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
