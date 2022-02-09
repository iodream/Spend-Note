#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/Income/GetIncomesHandler.h"
#include "Server/Handlers/Entities/Parsers.h"
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

void Compare(const Income& income, const db::Income& dbIncome, const db::IncomeCategory category)
{
	EXPECT_EQ(income.id, dbIncome.id);
	EXPECT_EQ(income.name, dbIncome.name);
	EXPECT_EQ(income.amount, dbIncome.amount);
	EXPECT_EQ(income.category.id, category.id);
	EXPECT_EQ(income.category.name, category.name);
	EXPECT_EQ(income.add_time, dbIncome.add_time);
	EXPECT_EQ(income.expiration_time, dbIncome.expiration_time.value_or(""));
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
	ASSERT_EQ(array.size(), 0);
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
	ASSERT_EQ(array.size(), 1);

	auto income_json = array[0].toObject();
	auto category_json = income_json["category"].toObject();

	IncomeJSONParser parser{};
	auto result = parser.Parse(income_json);

	Compare(result, income, category);
}
