#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Net/Parsing.h"

namespace  {

Income FormExpectedResult()
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

	return income;
}

void Compare(const Income& income1, const Income& income2)
{
	EXPECT_EQ(income1.id, income2.id);
	EXPECT_EQ(income1.category.id, income2.category.id);
	EXPECT_EQ(income1.category.name, income2.category.name);
	EXPECT_EQ(income1.amount, income2.amount);
	EXPECT_EQ(income1.name, income2.name);
	EXPECT_EQ(income1.add_time, income2.add_time);
	EXPECT_EQ(income1.expiration_time, income2.expiration_time);
}

}

TEST(IncomeJSONParser, PARSE)
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

	IncomeJSONParser parser{};

	auto result = parser.Parse(json);
	auto expected_result = FormExpectedResult();

	Compare(result, expected_result);
}
