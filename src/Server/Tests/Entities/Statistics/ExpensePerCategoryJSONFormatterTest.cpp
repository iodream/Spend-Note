#include "gtest/gtest.h"

#include <QJsonObject>

#include "Net/Entities/Statistics/StatisticPerCategory.h"
#include "Net/Tools/Formatters/Statistics/StatisticPerCategoryJSONFormatter.h"

namespace
{

QJsonObject FormJSON()
{
	QJsonObject object;

	object["category_id"] = 1;
	object["amount"] = 2;

	return object;
}

StatisticPerCategory FormExpense()
{
	StatisticPerCategory expense;

	expense.category_id = 1;
	expense.amount = 2;

	return expense;
}

}


TEST(ExpensePerCategoryJSONFormatter, FORMATTER)
{
	auto object = FormJSON();
	StatisticPerCategoryJSONFormatter m_formatter{};
	auto expense = m_formatter.Format(FormExpense());

	EXPECT_EQ(object["category_id"], expense["category_id"]);
	EXPECT_EQ(object["amount"], expense["amount"]);
}
