#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Net/Parsing.h"

namespace  {

std::vector<Income> FormExpectedIncomeVector()
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

	std::vector<Income> incomes;
	incomes.emplace_back(income);

	return incomes;
}

std::vector<Income> FormEmptyIncomeVector()
{
	std::vector<Income> incomes;
	return incomes;
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

TEST(IncomesJSONParser, ONE_INCOME)
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

	QJsonArray array;
	array.append(json);

	IncomesJSONParser parser{};

	auto result = parser.Parse(array);
	auto expected_result = FormExpectedIncomeVector();

	Income result_income, expected_result_income;
	for(auto& item : result)
	{
		result_income = item;
	}
	for(auto& item : expected_result)
	{
		expected_result_income = item;
	}
	Compare(result_income, expected_result_income);
}

TEST(IncomesJSONParser, NO_INCOMES)
{
	QJsonArray array;
	IncomesJSONParser parser{};
	auto result = parser.Parse(array);
	auto expected_result = FormEmptyIncomeVector();
	EXPECT_EQ(result.size(), expected_result.size());
}
