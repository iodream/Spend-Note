#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/Income/AddIncomeHandler.h"
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

namespace {

QJsonDocument FormatJSON()
{
	QJsonObject json;

	json["income_id"] = "";
	json["user_id"] = "1";
	json["name"] = "some_name";
	json["amount"] = 1;
	json["category_id"] = "1";
	json["add_time"] = "";
	json["expiration_time"] = "";

	return QJsonDocument{json};
}

}

TEST(AddIncomeHandler, ADD_INCOME)
{
	auto facade = std::make_unique<MockDbFacade>();
	EXPECT_CALL(*facade, AddIncome(_))
		.WillOnce(Return(std::optional<IdType>{1}));

	auto handler = std::make_unique<AddIncomeHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::USER_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_POST;
	{
		request.json_payload = FormatJSON();
	}

	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

	std::string income_id;
	SafeReadString(response.json_payload.object(), "id", income_id);
	EXPECT_EQ(income_id, "1");
}
