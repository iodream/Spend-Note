#pragma once

#include <QJsonDocument>

#include "Net/Entities/User/EmailUpdate.h"
#include "Net/Parsing.h"

class EmailUpdateJSONFormatter
{
public:
	QJsonDocument Format(const EmailUpdate& email_update);
};
