#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/AddIncomeHandler.h"
#include "Net/Parsing.h"
#include "Utils.h"

using ::testing::Return;
using ::testing::_;

namespace {

Income income
{
	1,
	1,
	"income 1",
	1,
	1,
	"some time",
	"some time 2"
};

void CheckIncomesEquality(const Income& i1, const Income& i2)
{
	EXPECT_EQ(i1.income_id, i2.income_id);
	EXPECT_EQ(i1.user_id, i2.user_id);
	EXPECT_EQ(i1.name, i2.name);
	EXPECT_EQ(i1.amount, i2.amount);
	EXPECT_EQ(i1.category_id, i2.category_id);
	EXPECT_EQ(i1.add_time, i2.add_time);
	EXPECT_EQ(i1.expiration_time, i2.expiration_time);
}

}

TEST(AddIncomeHandler, ADD_INCOME)
{
	auto facade = std::make_unique<MockDbFacade>();
	auto handler = std::make_unique<AddIncomeHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["income_id"] = "1";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

}
