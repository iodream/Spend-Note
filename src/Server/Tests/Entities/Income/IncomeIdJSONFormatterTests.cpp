#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Formatters.h"
#include "Net/Parsing.h"

namespace  {

QJsonObject FormExpectedJSON()
{
	QJsonObject json;

	json["id"] = 1;

	return json;
}

}

TEST(IncomeIdJSONFormatterTest, FORMAT)
{
	IncomeId income_id;
	income_id.id = 1;

	IncomeIdJSONFormatter formatter{};

	auto result = formatter.Format(income_id);
	auto expected_result = FormExpectedJSON();

	EXPECT_EQ(result["id"], expected_result["id"]);
}
