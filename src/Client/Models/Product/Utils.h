#pragma once

#include "DTO/Product.h"
#include "DTO/ProductCategory.h"
#include "DTO/ProductId.h"

#include "Net/Parsing.h"

Product ParseProduct(const QJsonObject& json);

QJsonDocument FormatProduct(const Product& product);

ProductId ParseProductId(const QJsonObject& json);

QJsonDocument FormatProductId(const ProductId& product_id);

ProductCategory ParseProductCategory(const QJsonObject& json);

QJsonDocument FormatProductCategory(const Product& category);
