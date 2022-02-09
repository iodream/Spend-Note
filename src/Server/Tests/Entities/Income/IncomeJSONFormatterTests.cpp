#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"
#include "Net/Parsing.h"

namespace  {

QJsonObject FormExpectedJSON()
{
	QJsonObject json, category;

	json["id"] = 1;

	category["id"] = 1;
	category["name"] = "name";
	json["category"] = category;

	json["amount"] = 1;
	json["name"] = "name";
	json["add_time"] = "";
	json["expiration_time"] = "";

	return json;
}

void Compare(const QJsonObject& object1, const QJsonObject& object2)
{
	EXPECT_EQ(object1["id"], object2["id"]);
	EXPECT_EQ(object1["category"].toObject(), object2["category"].toObject());
	EXPECT_EQ(object1["amount"], object2["amount"]);
	EXPECT_EQ(object1["name"].toString(), object2["name"].toString());
	EXPECT_EQ(object1["add_time"].toString(), object2["add_time"].toString());
	EXPECT_EQ(object1["expiration_time"].toString(), object2["expiration_time"].toString());
}

}

TEST(IncomeJSONFormatterTest, FORMAT)
{
	Income income;
	IncomeCategory category;

	income.id = 1;

	category.id = 1;
	category.name = "name";
	income.category = category;

	income.amount = 1;
	income.name = "name";
	income.add_time = "";
	income.expiration_time = "";

	IncomeJSONFormatter formatter{};

	auto result = formatter.Format(income);
	auto expected_result = FormExpectedJSON();

	Compare(result, expected_result);
}
