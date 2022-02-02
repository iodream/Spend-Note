#include <QJsonObject>

#include "Net/Parsing.h"
#include "ProductIdJSONParser.h"

ProductId ProductIdJSONParser::Parse(const QJsonObject &json)
{
	ProductId product_id;
	SafeReadId(json, "id", product_id.id);
	return product_id;
}
