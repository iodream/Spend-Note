#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"

namespace
{

QJsonObject FormObject()
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


TEST(ListIdJSONParser, PARSING)
{
	auto list_id = FormId();
	ListIdJSONParser m_parser;
	auto object =  m_parser.Parse(FormObject());

	EXPECT_EQ(list_id.id, object.id);
}
