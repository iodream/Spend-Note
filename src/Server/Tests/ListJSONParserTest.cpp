#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"


namespace
{
QJsonObject FormObject()
{
	QJsonObject obj, tmp_obj;

	obj["id"] = 1;
	obj["owner_id"] = 1;
	obj["name"] = "test_name";

	tmp_obj["id"] = 1;
	tmp_obj["name"] = "test_state";

	obj["state"] = tmp_obj;

	return obj;
}

List FormList()
{
	List list;

	list.id = 1;
	list.owner_id = 1;
	list.name = "test_name";
	list.state.id = 1;
	list.state.name = "test_state";

	return list;
}
}
TEST(ListJSONParser, PARSING)
{
	auto list = FormList();
	ListJSONParser m_parser{};
	auto object = m_parser.Parse(FormObject());


	EXPECT_EQ(object.id, list.id);
	EXPECT_EQ(object.owner_id, list.owner_id);
	EXPECT_EQ(object.name, list.name);
	EXPECT_EQ(object.state.id, list.state.id);
	EXPECT_EQ(object.state.name, list.state.name);
}
