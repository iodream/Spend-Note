#include <QJsonObject>

#include "Net/Parsing.h"
#include "ProductIdJSONParser.h"

ProductId ProductIdJSONParser::Parse(const QJsonDocument& json_doc)
{
	ProductId product_id;
	SafeReadId(json_doc.object(), "id", product_id.id);
	return product_id;
}
