#pragma once

#include "DTO/List.h"

#include "Net/Parsing.h"

List ParseList(const QJsonObject& json);

QJsonDocument FormatList(const List& list);
