#include "gtest/gtest.h"

#include <QJsonObject>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"

namespace
{

QJsonObject FormJSON()
{
	QJsonObject object;

	object["amount"] = 1;
	object["day"] = "Monday";

	return object;
}

StatisticPerDay FormExpense()
{
	StatisticPerDay expense;

	expense.amount = 1;
	expense.day = "Monday";

	return expense;
}

}


TEST(ExpensePerDayJSONParser, PARSER)
{
	auto object = FormExpense();
	StatisticPerDayJSONParser m_parser{};
	auto expense = m_parser.Parse(FormJSON());

	EXPECT_EQ(object.amount, expense.amount);
	EXPECT_EQ(object.day, expense.day);
}
