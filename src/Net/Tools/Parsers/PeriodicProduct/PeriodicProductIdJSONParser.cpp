#include <QJsonObject>

#include "Net/Parsing.h"
#include "PeriodicProductIdJSONParser.h"

PeriodicProductId PeriodicProductIdJSONParser::Parse(const QJsonObject& json)
{
	PeriodicProductId product_id;
	SafeReadId(json, "id", product_id.id);
	return product_id;
}
