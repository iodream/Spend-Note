#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <string>

#include "../Entities/ProductId.h"
#include "Net/Parsing.h"
#include "../Handlers/Common.h"

QJsonDocument ProductIdFormat(ProductId& product_id)
{
	QJsonObject json;
	SafeWriteId(json, "id", product_id.id);
	return QJsonDocument{json};
}
