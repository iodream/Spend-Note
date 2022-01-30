#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/LoginHandler.h"

#include <QDebug>

using ::testing::Return;
using ::testing::_;

TEST(LoginHandlerTest, USER_LOGIN_INVALID)
{
	auto facade = std::make_unique<MockDbFacade>();
	User existing_user;
	existing_user.id = 1;
	existing_user.login = "Test user1";
	existing_user.password = "Test password hash1";

	EXPECT_CALL(*facade, GetUserByLogin(_))
		.WillOnce(Return(std::optional{existing_user}));

	auto handler = std::make_unique<LoginHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["login"] = "Test user2";
		json["password"] = "Test password hash2";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->Handle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_UNAUTHORIZED);
}

TEST(LoginHandlerTest, USER_LOGIN_OK)
{
	auto facade = std::make_unique<MockDbFacade>();
	User existing_user;
	existing_user.id = 1;
	existing_user.login = "Test user";
	existing_user.password = "Test password hash";

	EXPECT_CALL(*facade, GetUserByLogin(_))
		.WillOnce(Return(std::optional{existing_user}));

	auto handler = std::make_unique<LoginHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["login"] = "Test user";
		json["password"] = "Test password hash";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->Handle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
}
