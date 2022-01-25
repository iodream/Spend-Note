#pragma once

#include <QString>

#include "../Common.h"

struct Income
{
	IdType income_id;
	IdType owner_id;
	QString name;
	double amount;
	IdType category_id;
	QString add_time;
	QString expiration_time;
};
