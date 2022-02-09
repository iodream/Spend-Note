#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"

#include "Server/Handlers/List/GetListsHandler.h"
#include "Server/Handlers/List/Utils.h"
#include "Net/Parsing.h"


using ::testing::Return;
using ::testing::_;

namespace  {

db::List l1 {
	1,
	1,
	1,
	"List 1",
};

db::ListState s1 {
	1,
	"State 1"
};

void CheckProductsEquality(const db::List& l1, const db::List& l2)
{
	EXPECT_EQ(l1.id, l2.id);
	EXPECT_EQ(l1.owner_id, l2.owner_id);
	EXPECT_EQ(l1.state_id, l2.state_id);
	EXPECT_EQ(l1.name, l2.name);
}

std::unique_ptr<GetListsHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetListsHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));
	return std::move(handler);
}


}

TEST(GetListsHandlerTest, EMPTY_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllLists(_))
		.WillOnce(Return(std::vector<db::List>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray lists = response.json_payload.array();
	EXPECT_EQ(lists.size(), 0);
}
/*
TEST(GetListsHandlerTest, ONE_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllLists(_))
		.WillOnce(Return(std::vector<db::List>{l1}));
	EXPECT_CALL(*facade, GetListStateById(1))
		.WillOnce(Return(std::optional<db::ListState>{s1}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray lists = response.json_payload.array();
	EXPECT_EQ(lists.size(), 1);

	auto list = lists.at(0).toObject();
	auto list_dto = ParseList(list);

	CheckProductsEquality(l1, list_dto);

	EXPECT_EQ(s1.id, list_dto.state_id);
	EXPECT_EQ(s1.name, list["state"].toString().toStdString());
}
*/
