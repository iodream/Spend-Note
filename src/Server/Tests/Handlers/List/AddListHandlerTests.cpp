#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/List/AddListHandler.h"
#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Net/Parsing.h"
#include "../libdal/Exceptions/SQLFailure.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Throw;

namespace {

QJsonDocument FormJSON()
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

std::unique_ptr<AddListHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<AddListHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}
TEST(AddListHandler, ADD_LIST_SUCCESS)
{
  auto facade = std::make_unique<MockDbFacade>();
  EXPECT_CALL(*facade, AddList(_))
	.WillOnce(Return(std::optional<db::IdType>{1}));

  auto handler = MakeHandler(std::move(facade));

  Net::Request request;
  request.method = Net::HTTP_METHOD_POST;

  request.json_payload = FormJSON();


  auto response = handler->AuthHandle(request);
  ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);

  ListIdJSONParser parser{};
  auto list_id = parser.Parse(response.json_payload.object());
  EXPECT_EQ(list_id.id, 1);
}

TEST(AddListHandler, ADD_LIST_FAILURE)
{
  auto facade = std::make_unique<MockDbFacade>();
  EXPECT_CALL(*facade, AddList(_))
	.WillOnce(Throw(db::SQLFailure("")));

  auto handler = MakeHandler(std::move(facade));

  Net::Request request;
  request.method = Net::HTTP_METHOD_POST;

  request.json_payload = FormJSON();


  auto response = handler->AuthHandle(request);
  ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CONFLICT);
}
