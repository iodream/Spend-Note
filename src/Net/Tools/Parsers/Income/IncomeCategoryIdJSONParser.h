#pragma once

#include <QJsonObject>

#include "Net/Entities/Income/IncomeCategoryId.h"
#include "Net/Parsing.h"

class IncomeCategoryIdJSONParser
{
public:
	IncomeCategoryId Parse(const QJsonObject& json);
};

