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

std::unique_ptr<UpdateListHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<UpdateListHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::LIST_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}

}

TEST(UpdateListHandler, UPDATE_LIST_SUCCESS)
{
	auto facade = std::make_unique<MockDbFacade>();

	db::List list;
	EXPECT_CALL(*facade, GetListById(1))
			.WillOnce(Return(std::optional<db::List>{list}));
	EXPECT_CALL(*facade, CanUserEditList(1, 1))
		.WillOnce(Return(true));
	EXPECT_CALL(*facade, UpdateList(_))
		.WillOnce(Return(true));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	request.json_payload = FormJSON();
	request.uid = 1;

	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}

TEST(UpdateListHandler, UPDATE_LIST_FAILURE)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetListById(1))
		.WillOnce(Return(std::optional<db::List>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	request.json_payload = FormJSON();

	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NOT_FOUND);
}
