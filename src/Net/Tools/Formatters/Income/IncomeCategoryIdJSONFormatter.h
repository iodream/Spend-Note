#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/Income/IncomeCategoryId.h"
#include "Net/Parsing.h"

class IncomeCategoryIdJSONFormatter
{
public:
	QJsonDocument Format(const IncomeCategoryId& category_id);
};
