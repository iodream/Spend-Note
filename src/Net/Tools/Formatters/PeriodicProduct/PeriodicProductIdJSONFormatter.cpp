#include <QJsonObject>

#include "PeriodicProductIdJSONFormatter.h"
#include "Net/Parsing.h"

QJsonObject PeriodicProductIdJSONFormatter::Format(const PeriodicProductId& product_id)
{
	QJsonObject json;
	WriteId(json, "id", product_id.id);
	return json;
}
