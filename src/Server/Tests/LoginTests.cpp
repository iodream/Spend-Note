#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/LoginHandler.h"
#include "Types.h"
#include <QDebug>
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

//checks for invalid login
TEST(LoginHandlerTest, USER_LOGIN_INVALID)
{
	auto facade = std::make_unique<MockDbFacade>();
	db::User existing_user;
	existing_user.id = 1;
	existing_user.login = "Test user";
	existing_user.password = "Test password hash";

	EXPECT_CALL(*facade, GetUserByLogin(_))
		.WillOnce(Return(std::optional{existing_user}));

	auto handler = std::make_unique<LoginHandler>();
	handler->set_facade(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["login"] = "Test user";
		json["password"] = "Test password hash1";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->Handle(request);
	auto dto = handler->m_parser.Parse(request.json_payload);

	ASSERT_NE(dto.password, existing_user.password);
}

//checks for good login
TEST(LoginHandlerTest, USER_LOGIN_OK)
{
	auto facade = std::make_unique<MockDbFacade>();
	db::User existing_user;
	existing_user.id = 1;
	existing_user.login = "Test user";
	existing_user.password = "Test password hash";

	EXPECT_CALL(*facade, GetUserByLogin(_))
		.WillOnce(Return(std::optional{existing_user}));

	auto handler = std::make_unique<LoginHandler>();
	handler->set_facade(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		QJsonObject json;
		json["login"] = "Test user"; // login data is the same
		json["password"] = "Test password hash";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->Handle(request);
	db::BigInt returned_id = response.json_payload["id"].toInt();
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);
	ASSERT_EQ(returned_id, existing_user.id);

}
