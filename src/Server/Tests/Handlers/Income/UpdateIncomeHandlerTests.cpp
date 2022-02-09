#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "../../MockDbFacade.h"
#include "Server/Handlers/Income/UpdateIncomeHandler.h"
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

TEST(UpdateIncomeHandler, UPDATE_INCOME)
{
	auto facade = std::make_unique<MockDbFacade>();
	EXPECT_CALL(*facade, UpdateIncome(_))
		.WillOnce(Return(true));

	auto handler = std::make_unique<UpdateIncomeHandler>();
	handler->set_facade(std::move(facade));

	Params params;
	params.Insert(Params::INCOME_ID, Params::Value{1});
	handler->set_params(std::move(params));

	Net::Request request;
	request.method = Net::HTTP_METHOD_PUT;
	request.json_payload = FormatJSON();

	auto response = handler->AuthHandle(request);
	ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
}
