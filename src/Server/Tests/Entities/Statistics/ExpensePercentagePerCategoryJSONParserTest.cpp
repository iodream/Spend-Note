#include "gtest/gtest.h"

#include <QJsonObject>

#include "Net/Entities/Statistics/StatisticPercentagePerCategory.h"
#include "Net/Tools/Parsers/Statistics/StatisticPercentagePerCategoryJSONParser.h"

namespace
{

QJsonObject FormJSON()
{
	QJsonObject object;

	object["category_id"] = 1;
	object["percentage"] = 2;

	return object;
}

StatisticPercentagePerCategory FormExpense()
{
	StatisticPercentagePerCategory expense;

	expense.category_id = 1;
	expense.percentage = 2;

	return expense;
}

}


TEST(ExpensePercentagePerCategoryJSONParser, PARSER)
{
	auto object = FormExpense();
	StatisticPercentagePerCategoryJSONParser m_parser{};
	auto expense = m_parser.Parse(FormJSON());

	EXPECT_EQ(object.category_id, expense.category_id);
	EXPECT_EQ(object.percentage, expense.percentage);
}
