#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"

namespace
{
QJsonObject FormExpectedJSON()
{
	QJsonObject object;

	object["id"] = 1;

	return object;
}

ListId FormId()
{
	ListId list_id;

	list_id.id = 1;

	return list_id;
}
}

TEST(ListIdJSONFormatter, FORMATTER)
{
	auto object = FormExpectedJSON();
	ListIdJSONFormatter m_formatter{};

	auto list_id = m_formatter.Format(FormId());

	EXPECT_EQ(object["id"], list_id["id"]);
}
