#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"


namespace
{
QJsonObject FormExpectedJSON()
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

void Compare(const QJsonObject& object, const QJsonObject& list)
{
	EXPECT_EQ(object["id"], list["id"]);
	EXPECT_EQ(object["owner_id"], list["owner_id"]);
	EXPECT_EQ(object["name"], list["name"]);
	EXPECT_EQ(object["state"], list["state"]);
}

}
TEST(ListJSONFormatter, FORMATTER)
{
	auto object = FormExpectedJSON();

	ListJSONFormatter m_formatter{};
	auto list = m_formatter.Format(FormList());

	Compare(object, list);
}
