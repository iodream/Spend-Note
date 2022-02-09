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

ProductId FormProduct()
{
	ProductId product_id;

	product_id.id = 1;

	return product_id;
}

}


TEST(ProductIdJSONFormatter, FORMATTER)
{
	auto object = FormExpectedJSON();
	ProductIdJSONFormatter m_formatter{};
	auto product_id = m_formatter.Format(FormProduct());

	EXPECT_EQ(object["id"], product_id["id"]);
}
