#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/List/RemoveListHandler.h"
#include "Net/Parsing.h"
#include "../libdal/Exceptions/SQLFailure.h"


using ::testing::Return;
using ::testing::_;

namespace  {

std::unique_ptr<RemoveListHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<RemoveListHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::LIST_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}

TEST(RemoveListHandlerTest, LIST_PRESENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, RemoveList(_))
		.WillOnce(Return(true));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(RemoveListHandlerTest, INCOME_ABSENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, RemoveList(_))
		.WillOnce(Return(false));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
