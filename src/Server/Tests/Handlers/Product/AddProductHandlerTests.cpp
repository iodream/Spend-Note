#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Facade/DbFacade.h"
#include "Server/Handlers/Product/AddProductHandler.h"
#include "Net/Parsing.h"


#include "../libdal/Exceptions/SQLFailure.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Throw;
namespace {

QJsonObject FormObject(int id)
{
	QJsonObject product, tmp_product;

	product["id"] = id;
	product["list_id"] = 1;

	tmp_product["id"] = 1;
	tmp_product["name"] = "test_name";

	product["category"] = tmp_product;
	product["name"] = "test_name";
	product["is_bought"] = true;
	product["amount"] = 1;
	product["price"] = 1;
	product["priority"] = 1;
	product["add_date"] = "test_date";
	product["purchase_date"] = "test_date";
	product["buy_until_date"] = "test_date";

	return product;
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

	EXPECT_CALL(*facade, CanUserEditList(1, 1))
		.WillOnce(Return(true));
	EXPECT_CALL(*facade, AddProduct(_))
		.WillOnce(Return(std::optional<db::IdType>{1}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.json_payload = QJsonDocument{FormObject(1)};
	request.method = Net::HTTP_METHOD_POST;
	request.uid = 1;


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
	EXPECT_CALL(*facade, CanUserEditList(1, 1))
		.WillOnce(Return(true));
	EXPECT_CALL(*facade, AddProduct(_))
		.WillOnce(Throw(db::SQLFailure("")));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.json_payload = QJsonDocument{FormObject(123)};
	request.method = Net::HTTP_METHOD_POST;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CONFLICT);
}
