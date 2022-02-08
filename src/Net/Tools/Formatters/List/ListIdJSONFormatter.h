#pragma once
#include <QJsonObject>

#include "Net/Entities/List/ListId.h"

#include "Net/Parsing.h"

class ListIdJSONFormatter
{
public:
	QJsonObject Format(const ListId& list_id);
};
