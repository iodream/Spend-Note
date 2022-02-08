#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"

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

TEST(ListsJSONFormatter, FORMATTER)
{
	auto objects = FormObjects();
	ListsJSONFormatter m_formatter{};
	auto lists = m_formatter.Format(FormLists());

	QJsonObject list_obj1, list_obj2;

	for(const QJsonValue& el : lists)
	{
		list_obj1 = el.toObject();
	}
	for(const QJsonValue& el : lists)
	{
		list_obj2 = el.toObject();
	}

	EXPECT_EQ(list_obj1["id"], list_obj2["id"]);
	EXPECT_EQ(list_obj1["owner_id"], list_obj2["owner_id"]);
	EXPECT_EQ(list_obj1["name"], list_obj2["name"]);
	EXPECT_EQ(list_obj1["state"], list_obj2["state"]);
}
