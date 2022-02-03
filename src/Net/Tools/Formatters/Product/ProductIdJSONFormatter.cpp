#include <QJsonObject>

#include "Net/Parsing.h"
#include "ProductIdJSONFormatter.h"

QJsonDocument ProductIdJSONFormatter::Format(const ProductId &product_id)
{
	QJsonObject json;
	WriteId(json, "id", product_id.id);
	return QJsonDocument{json};
}