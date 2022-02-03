#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Net/Parsing.h"
#include "Net/Entities/Income/Income.h"
#include "Net/Tools/Formatters/Income/IncomesJSONFormatter.h"

namespace {

QJsonDocument FormJSON()
{
	QJsonObject json, category;

	json["id"] = 0;

	category["id"] = 0;
	category["name"] = "name";
	json["category"] = category;

	json["amount"] = 0;
	json["name"] = "name";
	json["add_time"] = "";
	json["expiration_time"] = "";


	return QJsonDocument{json};
}

QJsonDocument FormEmptyJSON()
{
	QJsonArray array;

	return QJsonDocument{array};
}

}

TEST(FormIncomesJSON, DISABLED_ONE_INCOME)
{
	Income<std::string> income;

	income.id = 0;
	IncomeCategory<std::string> category;
	category.name = "name";
	category.id = 0;
	income.category = category;
	income.amount = 0;
	income.name = "name";
	income.add_time = "";
	income.expiration_time = "";

//	std::vector<Income<std::string>> incomes;
//	incomes.push_back(income);

	IncomeJSONFormatter<Income<std::string>> formatter;

//	auto result = formatter.Format(income);
	auto result = FormJSON();
	auto suggested_result = FormJSON();

	EXPECT_EQ(result, suggested_result);
}

TEST(FormIncomesJSON, NO_INCOMES)
{
	std::vector<Income<std::string>> incomes;
	IncomesJSONFormatter<Income<std::string>> formatter;

	auto result = formatter.Format(incomes);
	auto suggested_result = FormEmptyJSON();

	EXPECT_EQ(result, suggested_result);
}
