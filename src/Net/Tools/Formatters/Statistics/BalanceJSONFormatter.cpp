#include <QJsonObject>

#include "BalanceJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject BalanceJSONFormatter::Format(const Balance& balance)
{
	QJsonObject json;
	WriteMoney(json, "balance", balance.balance);
	WriteMoney(json, "planned_balance", balance.planned_balance);
	return json;
}
