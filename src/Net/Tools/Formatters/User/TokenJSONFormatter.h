#pragma once

#include "QJsonObject"
#include "Net/Entities/User/Token.h"
#include "Net/Parsing.h"

class TokenJSONFormatter
{
public:
	QJsonDocument Format(const Token& token);
};
