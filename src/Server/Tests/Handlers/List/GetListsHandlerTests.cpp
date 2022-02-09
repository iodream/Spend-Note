#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Server/Handlers/List/GetListsHandler.h"
#include "Server/Handlers/List/Utils.h"
#include "Net/Parsing.h"


using ::testing::Return;
using ::testing::_;

namespace  {

ListState list_state{
	1,
	"State 1"
};

List list{
	1,
	"List 1",
	1,
	list_state
};

db::List db_list{
	1,
	1,
	1,
	"List 1",
};

db::ListState db_list_state {
	1,
	"State 1"
};

void CheckListsEquality(const List& list1, const List& list2)
{
	EXPECT_EQ(list1.id, list2.id);
	EXPECT_EQ(list1.owner_id, list2.owner_id);
	EXPECT_EQ(list1.state.id, list2.state.id);
	EXPECT_EQ(list1.state.name, list2.state.name);
	EXPECT_EQ(list1.name, list2.name);
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

TEST(GetListsHandlerTest, ONE_LIST)
{
	ListJSONParser m_parser;

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllLists(_))
		.WillOnce(Return(std::vector<db::List>{db_list}));
	EXPECT_CALL(*facade, GetListStateById(1))
		.WillOnce(Return(std::optional<db::ListState>{db_list_state}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray lists = response.json_payload.array();
	EXPECT_EQ(lists.size(), 1);

	auto list = m_parser.Parse(lists[0].toObject());

	CheckListsEquality(list, ::list);
}

