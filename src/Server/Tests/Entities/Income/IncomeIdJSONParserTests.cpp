#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Net/Parsing.h"

namespace  {

IncomeId FormExpectedResult()
{
	IncomeId income_id;
	income_id.id = 1;
	return income_id;
}

}

TEST(IncomeIdJSONParserTest, PARSE)
{
	QJsonObject json;
	json["id"] = 1;

	IncomeIdJSONParser parser{};

	auto result = parser.Parse(json);
	auto expected_result = FormExpectedResult();

	EXPECT_EQ(result.id, expected_result.id);
}
