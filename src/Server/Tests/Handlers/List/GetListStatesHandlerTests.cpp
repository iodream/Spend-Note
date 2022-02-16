#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Server/Handlers/List/GetListStatesHandler.h"


using ::testing::Return;
using ::testing::_;

namespace  {

ListState list_state{
	1,
	"State 1"
};

db::ListState db_list_state {
	1,
	"State 1"
};

void CheckListStatesEquality(const ListState& list_state1, const ListState& list_state2)
{
	EXPECT_EQ(list_state1.id, list_state2.id);
	EXPECT_EQ(list_state1.name, list_state2.name);

}

std::unique_ptr<GetListStatesHandler> MakeHandler(std::unique_ptr<MockDbFacade>&& facade)
{
	auto handler = std::make_unique<GetListStatesHandler>();
	handler->set_facade(std::move(facade));

	return std::move(handler);
}

}

TEST(GetListStateHandlerTest, EMPTY_LIST)
{
	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllListStates())
		.WillOnce(Return(std::vector<db::ListState>{}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray lists = response.json_payload.array();
	EXPECT_EQ(lists.size(), 0);
}

TEST(GetListStatesHandlerTest, ONE_LIST_STATE)
{
	ListStateJSONParser m_parser;

	auto facade = std::make_unique<MockDbFacade>();

	EXPECT_CALL(*facade, GetAllListStates())
		.WillOnce(Return(std::vector<db::ListState>{db_list_state}));

	auto handler = MakeHandler(std::move(facade));

	Net::Request request;
	request.method = Net::HTTP_METHOD_GET;

	auto response = handler->AuthHandle(request);

	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	QJsonArray list_states = response.json_payload.array();
	EXPECT_EQ(list_states.size(), 1);

	auto state = m_parser.Parse(list_states[0].toObject());

	CheckListStatesEquality(state, list_state);
}

