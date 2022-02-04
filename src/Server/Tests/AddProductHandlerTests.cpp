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

std::unique_ptr<AddProductHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<AddProductHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::LIST_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}

ACTION(ThrowSQLFailure)
{
	throw db::SQLFailure("");
}

TEST(AddProductHandlerTest, SUCCESS)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, AddProduct(_))
		.WillOnce(Return(std::optional<db::IdType>{1}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		request.json_payload = FormTestJSON();
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);

	QJsonObject json = response.json_payload.object();
	db::IdType id;
	SafeReadId(json, "id", id);
	EXPECT_EQ(id, 1);
}

TEST(AddProductHandlerTest, FAILURE)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, AddProduct(_))
		.Times(1)
		.WillRepeatedly(ThrowSQLFailure());

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		request.json_payload = FormTestJSON();
	}

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CONFLICT);
}
