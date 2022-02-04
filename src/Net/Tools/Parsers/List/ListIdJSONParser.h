#pragma once
#include <QJsonObject>

#include "Net/Entities/List/ListId.h"
#include "Net/Parsing.h"

class ListIdJSONParser
{
public:
	ListId Parse(const QJsonObject& obj);
};
