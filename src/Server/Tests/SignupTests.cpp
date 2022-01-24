#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/SignupHandler.h"

#include <QDebug>

using ::testing::Return;
using ::testing::_;

TEST(SignupHandlerTest, USER_ALREADY_EXISTS)
{
	auto facade = std::make_unique<MockDbFacade>();
	User existing_user;
	existing_user.id = 1;
	existing_user.login = "Test user";
	existing_user.password = "Test password hash";

	EXPECT_CALL(*facade, GetUserByLogin(_))
		.WillOnce(Return(std::optional{existing_user}));

	auto handler = std::make_unique<SignupHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["login"] = "New user login";
		json["password"] = "New user password hash";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->Handle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CONFLICT);
}

TEST(SignupHandlerTest, USER_DOES_NOT_EXIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetUserByLogin(_))
		.WillOnce(Return(std::optional<User>{}));

	IdType id;
	EXPECT_CALL(*facade, AddUser(_))
		.WillOnce(Return(std::optional{id}));

	auto handler = std::make_unique<SignupHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["login"] = "New user login";
		json["password"] = "New user password hash";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->Handle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
}
