#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>
#include <QJsonDocument>

#include "MockDbFacade.h"
#include "../Handlers/List/ParserAndFormatter/ListEntity.h"
#include "../Handlers/List/ParserAndFormatter/ListJSONParser.cpp"

namespace {

ListEntity FormList()
{
	ListEntity list;

	list.id = 0;
	list.name = "test_name";
	list.owner_id = 0;
	list.state.first = 0;
	list.state.second = "test_state";

	return list;
}

}

TEST(ParseListJSON, PARSE)
{
	QJsonObject json, temp_json;
	ListJSONParser parser;

	json["id"] = 0;
	json["name"] = "test_name";
	json["owner_id"] = 0;

	temp_json["id"] = 0;
	temp_json["name"] = "test_state";
	json["state"] = temp_json;

	ListEntity result = parser.Parse(json);
	ListEntity suggested_result = FormList();

	EXPECT_EQ(result.id, suggested_result.id);
	EXPECT_EQ(result.name, suggested_result.name);
	EXPECT_EQ(result.owner_id, suggested_result.owner_id);
	EXPECT_EQ(result.state.first, suggested_result.state.first);
	EXPECT_EQ(result.state.second, suggested_result.state.second);

}
