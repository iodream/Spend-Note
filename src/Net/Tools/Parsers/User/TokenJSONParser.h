#pragma once

#include "QJsonObject"
#include "Net/Entities/User/Token.h"
#include "Net/Parsing.h"

class TokenJSONParser
{
public:
	Token Parse(const QJsonObject& json);
};
