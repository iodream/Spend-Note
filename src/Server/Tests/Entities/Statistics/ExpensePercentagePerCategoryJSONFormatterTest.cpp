#include "gtest/gtest.h"

#include <QJsonObject>

#include "Net/Entities/Statistics/StatisticPercentagePerCategory.h"
#include "Net/Tools/Formatters/Statistics/StatisticPercentagePerCategoryJSONFormatter.h"

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


TEST(ExpensePercentagePerCategoryJSONFormatter, FORMATTER)
{
	auto object = FormJSON();
	StatisticPercentagePerCategoryJSONFormatter m_formatter{};
	auto expense = m_formatter.Format(FormExpense());

	EXPECT_EQ(object["category_id"], expense["category_id"]);
	EXPECT_EQ(object["amount"], expense["amount"]);
}
