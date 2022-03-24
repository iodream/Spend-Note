#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Server/Handlers/Statistics/GetBalanceHandler.h"
#include "Net/Parsing.h"


using ::testing::Return;
using ::testing::_;

namespace  {

Money db_balance = 1;
Money db_planned_balance = 2;

Balance balance{
	1,
	2
};

std::unique_ptr<GetBalanceHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetBalanceHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}


TEST(GetBalanceHandlerTest, BALANCE)
{
	BalanceJSONParser m_parser;

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, CalculateBalanceForUser(1))
		.WillOnce(Return(Money{db_balance}));
	EXPECT_CALL(*facade, CalculatePlannedBalanceForUser(1))
		.WillOnce(Return(Money{db_planned_balance}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	auto balance = m_parser.Parse(response.json_payload.object());

	EXPECT_EQ(balance.balance, ::balance.balance);
	EXPECT_EQ(balance.planned_balance, ::balance.planned_balance);
}

