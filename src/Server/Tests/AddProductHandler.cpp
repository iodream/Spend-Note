#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Product/AddProductHandler.h"
#include "Net/Parsing.h"

#include "../libdal/Exceptions/SQLFailure.h"

using ::testing::Return;
using ::testing::_;

namespace {

QJsonDocument FormTestJSON() {
	QJsonObject json;

	json["id"] = "";
	json["list_id"] = "1";
	json["category_id"] = "1";
	json["name"] = "Name?";
	json["price"] = 123;
	json["amount"] = 123;
	json["priority"] = 0;
	json["is_bought"] = false;
	json["add_date"] = "today";

	json["purchase_date"] = "";
	json["buy_until_date"] = "";
	return QJsonDocument(json);
}

}

ACTION(ThrowSQLFailure)
{
	throw SQLFailure("");
}

TEST(AddProductHandlerTest, SUCCESS)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, AddProduct(_))
		.WillOnce(Return(std::optional<IdType>{1}));

	auto handler = std::make_unique<AddProductHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		request.json_payload = FormTestJSON();
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);

	QJsonObject json = response.json_payload.object();
	IdType id;
	SafeReadId(json, "id", id);
	EXPECT_EQ(id, 1);
}

TEST(AddProductHandlerTest, FAILURE)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, AddProduct(_))
		.Times(1)
		.WillRepeatedly(ThrowSQLFailure());

	auto handler = std::make_unique<AddProductHandler>(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		request.json_payload = FormTestJSON();
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CONFLICT);
}
