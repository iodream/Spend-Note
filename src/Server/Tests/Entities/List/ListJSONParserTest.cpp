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

void Testing(const List& list_obj1, const List& list_obj2)
{
	EXPECT_EQ(list_obj1.id, list_obj2.id);
	EXPECT_EQ(list_obj1.owner_id, list_obj2.owner_id);
	EXPECT_EQ(list_obj1.name, list_obj2.name);
	EXPECT_EQ(list_obj1.state.id, list_obj2.state.id);
	EXPECT_EQ(list_obj1.state.name, list_obj2.state.name);
}

}
TEST(ListJSONParser, PARSING)
{
	auto list = FormList();
	ListJSONParser m_parser{};
	auto object = m_parser.Parse(FormObject());

	Testing(list, object);
}
