#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template<class StatisticPerDay>
class StatisticPerDayJSONParserBase
{
public:
	StatisticPerDay Parse(const QJsonObject& obj)
	{
		StatisticPerDay expense;

		SafeReadString(obj, "day", expense.day);
		SafeReadMoney(obj, "amount", expense.amount);

		return expense;
	}
};
