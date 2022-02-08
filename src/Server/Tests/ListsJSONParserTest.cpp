#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"

namespace
{
QJsonArray FormObjects()
{
	QJsonObject object, tmp_object;

	object["id"] = 1;
	object["owner_id"] = 1;
	object["name"] = "test_name";

	tmp_object["id"] = 1;
	tmp_object["name"] = "test_state";

	object["state"] = tmp_object;

	return QJsonArray{object};
}

std::vector<List> FormLists()
{
	std::vector<List> lists;
	List list;

	list.id = 1;
	list.owner_id = 1;
	list.name = "test_name";
	list.state.id = 1;
	list.state.name = "test_state";

	lists.push_back(list);
	return lists;
}
}

TEST(ListsJSONParser, PARSING)
{
	auto lists = FormLists();
	ListsJSONParser m_parser{};
	auto objects = m_parser.Parse(FormObjects());

	List list_obj1, list_obj2;

	for(const auto& el : lists)
	{
		list_obj1 = el;
	}

	for(const auto& el : objects)
	{
		list_obj2 = el;
	}
	EXPECT_EQ(list_obj1.id, list_obj2.id);
	EXPECT_EQ(list_obj1.owner_id, list_obj2.owner_id);
	EXPECT_EQ(list_obj1.name, list_obj2.name);
	EXPECT_EQ(list_obj1.state.id, list_obj2.state.id);
	EXPECT_EQ(list_obj1.state.name, list_obj2.state.name);
}








