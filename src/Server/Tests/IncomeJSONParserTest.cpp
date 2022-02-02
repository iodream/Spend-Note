#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Net/Parsing.h"
#include "Net/Entities/Income/Income.h"
#include "Net/Tools/Parsers/Income/IncomeJSONParser.h"

namespace {

Income<std::string> FormIncome()
{
	Income<std::string> income;
	IncomeCategory<std::string> category;

	income.id = 0;

	category.id = 0;
	category.name = "name";
	income.category= category;

	income.name = "name";
	income.amount = 0;
	income.add_time = "";
	income.expiration_time = "";

	return income;
}

}

TEST(ParseIncomesJSON, PARSE)
{
	QJsonObject json_object, category;

	json_object["id"] = 0;

	category["id"] = 0;
	category["name"] = "name";
	json_object["category"] = category;

	json_object["amount"] = 0;
	json_object["name"] = "name";
	json_object["add_time"] = "";
	json_object["expiration_time"] = "";

	auto json = QJsonDocument{json_object};

	IncomeJSONParser<Income<std::string>> parser;

	auto result = parser.Parse(json.object());
	auto suggested_result = FormIncome();

	EXPECT_EQ(result.id, suggested_result.id);
	EXPECT_EQ(result.category.id, suggested_result.category.id);
	EXPECT_EQ(result.category.name, suggested_result.category.name);
	EXPECT_EQ(result.name, suggested_result.name);
	EXPECT_EQ(result.amount, suggested_result.amount);
	EXPECT_EQ(result.add_time, suggested_result.add_time);
	EXPECT_EQ(result.expiration_time, suggested_result.expiration_time);
}
