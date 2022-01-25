#pragma once

#include <QString>

#include "../Common.h"

struct Product
{
	IdType id;
	IdType list_id;
	IdType category_id;
	QString name;
	double price;
	BigInt amount;
	int product_priority;
	bool is_bought;
	QString add_date;
	QString purchase_date;
	QString buy_until_date;
};
