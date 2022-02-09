#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"
#include "Net/Parsing.h"

namespace  {

QJsonArray FormJSONArray()
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

	return array;
}

QJsonArray FormEmptyJSONArray()
{
	return QJsonArray();
}

void Compare(const QJsonObject& o1, const QJsonObject& o2)
{
	EXPECT_EQ(o1["id"], o2["id"]);
	EXPECT_EQ(o1["category"].toObject(), o2["category"].toObject());
	EXPECT_EQ(o1["amount"], o2["amount"]);
	EXPECT_EQ(o1["name"].toString(), o2["name"].toString());
	EXPECT_EQ(o1["add_time"].toString(), o2["add_time"].toString());
	EXPECT_EQ(o1["expiration_time"].toString(), o2["expiration_time"].toString());
}

}

TEST(IncomesJSONFormatterTest, ONE_INCOME)
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

	IncomesJSONFormatter formatter{};

	auto result = formatter.Format(incomes);
	auto expected_result = FormJSONArray();

	QJsonObject result_item, expected_result_item;
	for(const QJsonValue& item : result)
	{
		result_item = item.toObject();
	}
	for(const QJsonValue& item : expected_result)
	{
		expected_result_item = item.toObject();
	}

	Compare(result_item, expected_result_item);
}

TEST(IncomesJSONFormatterTest, NO_INCOMES)
{
	std::vector<Income> incomes;
	IncomesJSONFormatter formatter{};
	auto result = formatter.Format(incomes);
	auto expected_result = FormEmptyJSONArray();
	EXPECT_EQ(result, expected_result);
}
