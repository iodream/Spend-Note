#pragma once

#include <QString>

#include "../Common.h"

#include "ProductCategory.h"

struct Product
{
	IdType id;
	IdType list_id;
	ProductCategory category;
	bool is_bought;
	QString name;
	BigInt amount;
	Money price;
	int priority;
	QString add_date;
	QString purchase_date;
	QString buy_until_date;
};
