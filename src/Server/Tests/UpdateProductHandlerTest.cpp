#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Product/UpdateProductHandler.h"
#include "Server/Handlers/Product/Utils.h"
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

TEST(UpdateList, LIST_PRESENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, UpdateList(_))
		.WillOnce(Return(true));

	auto handler = std::make_unique<UpdateProductHandler>();

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	{
		QJsonObject json;

		json["id"] = "7";
		json["list_id"] = "2";
		json["category_id"] = "2";
		json["price"] = "345";
		json["priority"] = "1";
		json["is_bought"] = true;
		json["add_date"] = "10-10-2012";
		json["purchase_date"] = "10-10-2012";
		json["buy_until_date"] = "10-10-2012";

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

	auto handler = std::make_unique<UpdateProductHandler>();

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	{
		QJsonObject json;

		json["id"] = "7123";
		json["list_id"] = "2";
		json["category_id"] = "2";
		json["price"] = "345";
		json["priority"] = "1";
		json["is_bought"] = true;
		json["add_date"] = "10-10-2012";
		json["purchase_date"] = "10-10-2012";
		json["buy_until_date"] = "10-10-2012";


		request.json_payload = QJsonDocument(json);
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
