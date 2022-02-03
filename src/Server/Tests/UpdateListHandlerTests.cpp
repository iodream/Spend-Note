#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/List/UpdateListHandler.h"
#include "Server/Handlers/List/Utils.h"
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

TEST(UpdateList, LIST_PRESENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, UpdateList(_))
		.WillOnce(Return(true));

	auto handler = std::make_unique<UpdateListHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	{
		QJsonObject json;
		json["list_id"] = "7";
		json["owner_id"] = "2";
		json["state_id"] = "2";
		json["name"] = "updated";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(UpdateIncomeHandlerTest, LIST_ABSENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, UpdateList(_))
		.WillOnce(Return(false));

	auto handler = std::make_unique<UpdateListHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	{
		QJsonObject json;

		json["list_id"] = "15";
		json["owner_id"] = "1";
		json["state_id"] = "2";
		json["name"] = "name";

		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
