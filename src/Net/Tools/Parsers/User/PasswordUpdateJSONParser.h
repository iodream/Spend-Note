#pragma once

#include "QJsonObject"
#include "Net/Entities/User/PasswordUpdate.h"
#include "Net/Parsing.h"

class PasswordUpdateJSONParser
{
public:
	PasswordUpdate Parse(const QJsonObject& json);
};

