#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Income/AddIncomeHandler.h"
#include "Net/Parsing.h"
#include "../Handlers/Income/DTO/IncomeOut.h"

namespace {

QJsonDocument FormJSON()
{
	QJsonObject json_array, category, json;
	QJsonArray array;

	json_array["id"] = 0;

	category["id"] = 0;
	category["name"] = "name";
	json_array["category"] = category;

	json_array["amount"] = 0;
	json_array["name"] = "name";
	json_array["add_time"] = "";
	json_array["expiration_time"] = "";

	array.append(json_array);

	json["incomes"] = array;

	return QJsonDocument{json};
}

QJsonDocument FormEmptyJSON()
{
	QJsonObject json;
	QJsonArray array;

	json["incomes"] = array;

	return QJsonDocument{json};
}

}

TEST(FormIncomesJSON, ONE_INCOME)
{
	IncomeOut income_out;
	income_out.id = 0;
	income_out.category_name = "name";
	income_out.name = "name";
	income_out.amount = 0;
	income_out.add_time = "";
	income_out.expiration_time = "";

	Incomes incomes;
	incomes.push_back(income_out);

	IncomeJSONFormatter formatter;

	auto result = formatter.Format(incomes);

	auto suggested_result = FormJSON();

	EXPECT_EQ(result, suggested_result);
}

TEST(FormIncomesJSON, NO_INCOMES)
{
	Incomes incomes;
	IncomeJSONFormatter formatter;

	auto result = formatter.Format(incomes);
	auto suggested_result = FormEmptyJSON();

	EXPECT_EQ(result, suggested_result);
}
