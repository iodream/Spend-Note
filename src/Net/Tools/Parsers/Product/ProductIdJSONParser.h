#pragma once

#include "QJsonDocument"
#include "../../../Entities/ProductId.h"

class ProductIdJSONParser
{
public:
	ProductId Parse(const QJsonDocument& json_doc);
};
