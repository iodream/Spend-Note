#include "gtest/gtest.h"

#include <QJsonDocument>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"

namespace
{

QJsonObject FormJSON()
{
	QJsonObject object;

	object["amount"] = 1;
	object["day"]  = "Monday";

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

TEST(ExpensePerDayJSONFormatter, FORMAT)
{
	auto object = FormJSON();
	StatisticPerDayJSONFormatter m_formatter{};
	auto expense = m_formatter.Format(FormExpense());

	EXPECT_EQ(object["amount"], expense["amount"]);
	EXPECT_EQ(object["day"], expense["day"]);
}
