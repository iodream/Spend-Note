#pragma once

#include "DTO/Product.h"

#include "Net/Parsing.h"

Product ParseProduct(const QJsonObject& json);

QJsonDocument FormatProduct(const Product& product);
