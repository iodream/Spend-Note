#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Income/AddIncomeHandler.h"
#include "Net/Parsing.h"
//#include "../Handlers/Income/DTO/IncomeIn.h"

namespace {

Income FormIncome()
{
	Income income;
	IncomeCategoryIn category;

	income.income_id = 0;

	category.id = 0;
	income.category_id = category.id;

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

	IncomeJSONParser parser;


	Income result = parser.Parse(json);
	Income suggested_result = FormIncome();

	EXPECT_EQ(result.income_id, suggested_result.income_id);
	EXPECT_EQ(result.category_id, suggested_result.category_id);
	EXPECT_EQ(result.name, suggested_result.name);
	EXPECT_EQ(result.amount, suggested_result.amount);
	EXPECT_EQ(result.add_time, suggested_result.add_time);
	EXPECT_EQ(result.expiration_time.value_or(""), suggested_result.expiration_time.value_or(""));
}
