#pragma once

#include <QJsonDocument>

#include "Net/Entities/Product/ProductId.h"

class ProductIdJSONFormatter
{
public:
	QJsonObject Format(const ProductId& product_id);
};
