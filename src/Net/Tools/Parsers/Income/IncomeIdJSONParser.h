#pragma once

#include <QJsonObject>
#include <QJsonDocument>

#include "Net/Entities/Income/IncomeId.h"
#include "Net/Parsing.h"

class IncomeIdJSONParser
{
public:
	IncomeId Parse(const QJsonObject& json);
};
