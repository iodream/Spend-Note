#include <QJsonObject>

#include "Net/Parsing.h"
#include "BalanceJSONParser.h"

Balance BalanceJSONParser::Parse(const QJsonObject& json)
{
	Balance balance;
	SafeReadMoney(json, "balance", balance.balance);
	SafeReadMoney(json, "planned_balance", balance.planned_balance);
	return balance;
}
