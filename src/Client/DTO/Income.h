#pragma once

#include <QString>

#include "../Common.h"
#include "IncomeCategory.h"

struct Income
{
	IdType id;
	IncomeCategory category;
	QString name;
	double amount;
	QString add_time;
	QString expiration_time;
};
