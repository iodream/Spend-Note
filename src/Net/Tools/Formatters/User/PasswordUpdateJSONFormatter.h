#pragma once

#include "QJsonObject"
#include "Net/Entities/User/PasswordUpdate.h"
#include "Net/Parsing.h"

class PasswordUpdateJSONFormatter
{
public:
	QJsonDocument Format(const PasswordUpdate& password_update);
};

