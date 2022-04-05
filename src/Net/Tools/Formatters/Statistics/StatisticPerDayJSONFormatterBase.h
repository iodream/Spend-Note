#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template<class StatisticPerDay>
class StatisticPerDayJSONFormatterBase
{
public:
	QJsonObject Format(const StatisticPerDay& expense)
	{
		QJsonObject json;
		WriteString(json, "day", expense.day);
		WriteMoney(json, "amount", expense.amount);
		return json;
	}
};
