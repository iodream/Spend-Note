#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/List/UpdateListHandler.h"
#include "Net/Parsing.h"
#include "../libdal/Exceptions/SQLFailure.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Throw;

namespace {

QJsonDocument FormatJSON()
{
  QJsonObject json, state;

  state["id"] = 1;
  state["name"] = "State 1";

  json["id"] = 1;
  json["owner_id"] = 1;
  json["name"] = "name";
  json["state"] = state;


  return QJsonDocument{json};
}

}

TEST(UpdateListHandler, UPDATE_LIST_SUCCESS)
{
	auto facade = std::make_unique<MockDbFacade>();
	EXPECT_CALL(*facade, UpdateList(_))
		.WillOnce(Return(true));

	auto handler = std::make_unique<UpdateListHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::LIST_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	request.json_payload = FormatJSON();

	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(UpdateListHandler, UPDATE_LIST_FAILURE)
{
	auto facade = std::make_unique<MockDbFacade>();
	EXPECT_CALL(*facade, UpdateList(_))
		.WillOnce(Return(false));

	auto handler = std::make_unique<UpdateListHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::LIST_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	request.json_payload = FormatJSON();

	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
