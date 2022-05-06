#pragma once

#include "QJsonObject"
#include "Net/Entities/User/EmailUpdate.h"
#include "Net/Parsing.h"

class EmailUpdateJSONParser
{
public:
	EmailUpdate Parse(const QJsonObject& json);
};
