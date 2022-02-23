#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template<class ExpensePerDay>
class ExpensePerDayJSONParserBase
{
public:
	ExpensePerDay Parse(const QJsonObject& obj)
	{
		ExpensePerDay expense;

		SafeReadString(obj, "day", expense.day);
		SafeReadMoney(obj, "amount", expense.amount);

		return expense;
	}
};
