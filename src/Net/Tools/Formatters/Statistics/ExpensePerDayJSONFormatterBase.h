#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template<class ExpensePerDay>
class ExpensePerDayJSONFormatterBase
{
public:
	QJsonObject Format(const ExpensePerDay& expense)
	{
		QJsonObject json;
		WriteString(json, "day", expense.day);
		WriteMoney(json, "amount", expense.amount);
		return json;
	}
};
