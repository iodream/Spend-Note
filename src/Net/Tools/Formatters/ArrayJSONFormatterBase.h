#pragma once
#include <QJsonObject>

#include "Net/Parsing.h"

template <typename ItemFormatter, typename Item>
class ArrayJSONFormatterBase
{
public:
	QJsonArray Format(const std::vector<Item>& items)
	{
		QJsonArray array;
		ItemFormatter formatter{};

		for (const auto& item: items)
		{
			array.append(formatter.Format(item));
		}

		return array;
	}
};
