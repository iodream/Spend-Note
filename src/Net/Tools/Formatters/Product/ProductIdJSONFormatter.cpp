#include <QJsonObject>

#include "ProductIdJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject ProductIdJSONFormatter::Format(const ProductId& product_id)
{
	QJsonObject json;
	WriteId(json, "id", product_id.id);
	return json;
}
