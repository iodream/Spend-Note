#include "gtest/gtest.h"

#include <QJsonObject>

#include "Net/Entities/Statistics/ExpensePerCategory.h"
#include "Net/Tools/Parsers/Statistics/ExpensePerCategoryJSONParser.h"

namespace
{

QJsonObject FormJSON()
{
	QJsonObject object;

	object["category_id"] = 1;
	object["amount"] = 2;

	return object;
}

ExpensePerCategory FormExpense()
{
	ExpensePerCategory expense;

	expense.category_id = 1;
	expense.amount = 2;

	return expense;
}

}


TEST(ExpensePerCategoryJSONParser, PARSER)
{
	auto object = FormExpense();
	ExpensePerCategoryJSONParser m_parser{};
	auto expense = m_parser.Parse(FormJSON());

	EXPECT_EQ(object.category_id, expense.category_id);
	EXPECT_EQ(object.amount, expense.amount);
}
