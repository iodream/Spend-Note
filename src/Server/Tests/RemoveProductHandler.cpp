#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Product/RemoveProductHandler.h"
#include "Server/Handlers/Product/Utils.h"
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

TEST(RemoveProductsHandlerTest, PRODUCT_PRESENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, ProductExists(_))
		.WillOnce(Return(true));
	EXPECT_CALL(*facade, RemoveProduct(_))
		.Times(1);

	auto handler = std::make_unique<RemoveProductHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;
	{
		QJsonObject json;
		json["id"] = "1";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(RemoveProductsHandlerTest, PRODUCT_ABSENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, ProductExists(_))
		.WillOnce(Return(false));

	auto handler = std::make_unique<RemoveProductHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;
	{
		QJsonObject json;
		json["id"] = "1";
		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
