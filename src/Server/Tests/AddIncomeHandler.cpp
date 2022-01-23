#include <memory>

#include "gtest/gtest.h"
#include <QJsonObject>

#include "MockDbFacade.h"
#include "Server/Handlers/AddIncomeHandler.h"
#include "Net/Parsing.h"

using ::testing::Return;
using ::testing::_;

namespace {

Income income
{
  1,
  1,
  "income 1",
  1,
  1,
  "some time",
  "some time 2"
};

}

TEST(AddIncomeHandler, ADD_INCOME)
{
  auto facade = std::make_unique<MockDbFacade>();
  EXPECT_CALL(*facade, AddIncome(_)).WillOnce(Return(std::optional<IdType>{}));
  auto handler = std::make_unique<AddIncomeHandler>(std::move(facade));

  Net::Request request;
  request.method = Net::HTTP_METHOD_POST;
  {
	QJsonObject json;
	json["income_id"] = "1";
	request.json_payload = QJsonDocument(json);
  }

  auto response = handler->AuthHandle(request);
  ASSERT_EQ(response.status, Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK);

  std::string income_id;
  SafeReadString(response.json_payload.object(), "id", income_id);
  EXPECT_EQ(income_id, "1");
}
