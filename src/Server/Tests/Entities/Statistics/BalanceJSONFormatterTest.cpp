#include "gtest/gtest.h"

#include <QJsonObject>

#include "Net/Entities/Statistics/Balance.h"
#include "Net/Tools/Formatters/Statistics/BalanceJSONFormatter.h"

namespace
{

QJsonObject FormJSON()
{
	QJsonObject object;

	object["balance"] = 1;
	object["planned_balance"] = 2;

	return object;
}

Balance FormBalance()
{
	Balance balance;

	balance.balance = 1;
	balance.planned_balance = 2;

	return balance;
}

}


TEST(BalanceJSONFormatter, FORMATTER)
{
	auto object = FormJSON();
	BalanceJSONFormatter m_formatter{};
	auto balance = m_formatter.Format(FormBalance());

	EXPECT_EQ(object["balance"], balance["balance"]);
	EXPECT_EQ(object["planned_balance"], balance["planned_balance"]);
}
