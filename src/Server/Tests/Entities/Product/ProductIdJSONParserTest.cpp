#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"

namespace
{

QJsonObject FormExpectedJSON()
{
	QJsonObject object;

	object["id"] = 1;

	return object;
}

ProductId FormProduct()
{
	ProductId product_id;

	product_id.id = 1;

	return product_id;
}

}


TEST(ProductIdJSONParser, PARSING)
{
	auto object = FormProduct();
	ProductIdJSONParser m_parser{};
	auto product_id = m_parser.Parse(FormExpectedJSON());

	EXPECT_EQ(object.id, product_id.id);
}
