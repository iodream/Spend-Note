#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/Income/AddIncomeHandler.h"
#include "Server/Handlers/Entities/Entities.h"
#include "Server/Handlers/Entities/Parsers.h"
#include "Net/Parsing.h"
#include "../libdal/Exceptions/SQLFailure.h"

using ::testing::Return;
using ::testing::_;
using ::testing::Throw;

namespace {

QJsonDocument FormatJSON()
{
	QJsonObject json, category;

	json["id"] = 1;
	category["id"] = 1;
	category["name"] = "name";
	json["category"] = category;
	json["name"] = "name";
	json["amount"] = 1;
	json["add_time"] = "";
	json["expiration_time"] = "";

	return QJsonDocument{json};
}

}

TEST(AddIncomeHandler, ADD_INCOME_SUCCESS)
{
	auto facade = std::make_unique<MockDbFacade>();
	EXPECT_CALL(*facade, AddIncome(_))
		.WillOnce(Return(std::optional<db::IdType>{1}));

	auto handler = std::make_unique<AddIncomeHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;

	request.json_payload = FormatJSON();


	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CREATED);

	IncomeIdJSONParser parser{};
	auto income_id = parser.Parse(response.json_payload.object());
	EXPECT_EQ(income_id.id, 1);
}

TEST(AddIncomeHandler, ADD_INCOME_FAILURE)
{
	auto facade = std::make_unique<MockDbFacade>();
	EXPECT_CALL(*facade, AddIncome(_))
		.WillOnce(Throw(db::SQLFailure("")));

	auto handler = std::make_unique<AddIncomeHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;

	request.json_payload = FormatJSON();


	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_CONFLICT);
}
