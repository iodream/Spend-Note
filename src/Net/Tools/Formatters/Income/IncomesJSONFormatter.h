#pragma once
#include <QJsonObject>

#include "Net/Entities/Income/Income.h"
#include "Net/Parsing.h"
#include "IncomeJSONFormatter.h"

template<class Entity>
class IncomesJSONFormatter
{
public:
	QJsonDocument Format(const std::vector<Entity>& incomes)
	{
		QJsonArray array;
		IncomesJSONFormatter<Entity> formatter{};

		for (const auto& incoms: incomes)
		{
			array.append(formatter.Format(incomes).object());
		}

		return QJsonDocument{array};
	}
};
