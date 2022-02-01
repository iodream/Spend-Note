#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <string>

#include "../Entities/ProductId.h"
#include "Net/Parsing.h"
#include "../Handlers/Common.h"

ProductId ProductIdParser(QJsonObject& json)
{
	ProductId product_id;
	SafeReadId(json, "id", product_id.id);
	return product_id;
}
