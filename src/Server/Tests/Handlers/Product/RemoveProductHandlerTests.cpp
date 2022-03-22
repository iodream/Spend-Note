#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/Product/RemoveProductHandler.h"
#include "Server/Handlers/Entities/Entities.h"
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

namespace  {

std::unique_ptr<RemoveProductHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<RemoveProductHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::PRODUCT_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}

TEST(RemoveProductsHandlerTest, PRODUCT_PRESENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	db::Product product;
	EXPECT_CALL(*facade, GetProductById(1))
		.WillOnce(Return(std::optional<db::Product>{product}));
	EXPECT_CALL(*facade, CanUserEditProduct(1, 1))
		.WillOnce(Return(true));
	EXPECT_CALL(*facade, RemoveProduct(_))
		.WillOnce(Return(true));

	auto handler = MakeHandler(std::move(facade));

	 Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;
	request.uid = 1;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(RemoveProductsHandlerTest, PRODUCT_ABSENT)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetProductById(1))
		.WillOnce(Return(std::optional<db::Product>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_DELETE;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
