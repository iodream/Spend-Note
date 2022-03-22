#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>


#include "../../MockDbFacade.h"
#include "Server/Handlers/Income/RemoveIncomeHandler.h"
#include "Net/Parsing.h"
#include "../libdal/Exceptions/SQLFailure.h"


using ::testing::Return;
using ::testing::_;

namespace  {

std::unique_ptr<RemoveIncomeHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<RemoveIncomeHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::INCOME_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}

TEST(RemoveIncomeHandlerTest, INCOME_PRESENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	db::Income income;
	EXPECT_CALL(*facade, GetIncomeById(1))
			.WillOnce(Return(std::optional<db::Income>{income}));
	EXPECT_CALL(*facade, CanUserEditIncome(1, 1))
		.WillOnce(Return(true));
	EXPECT_CALL(*facade, RemoveIncome(_))
		.WillOnce(Return(true));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(RemoveIncomeHandlerTest, INCOME_ABSENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetIncomeById(1))
			.WillOnce(Return(std::optional<db::Income>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
