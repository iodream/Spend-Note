#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/Product/UpdateProductHandler.h"
#include "Server/Handlers/Entities/Entities.h"
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

namespace  {

std::unique_ptr<UpdateProductHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<UpdateProductHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::PRODUCT_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

QJsonObject FormObject(int id, int list_id)
{
	QJsonObject product, tmp_product;

	product["id"] = id;
	product["list_id"] = list_id;

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

}

TEST(UpdateProduct, PRODUCT_PRESENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	db::Product product;
	EXPECT_CALL(*facade, GetProductById(1))
		.WillOnce(Return(product));
	EXPECT_CALL(*facade, CanUserEditProduct(1, 1))
		.WillOnce(Return(true));
	EXPECT_CALL(*facade, UpdateProduct(_))
		.WillOnce(Return(true));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.json_payload = QJsonDocument{FormObject(1, 1)};
	request.method = Net::HTTP_METHOD_PUT;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(UpdateProductHandlerTest, PRODUCT_ABSENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetProductById(1))
		.WillOnce(Return(std::optional<db::Product>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.json_payload = QJsonDocument{FormObject(1, 12)};
	request.method = Net::HTTP_METHOD_PUT;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
