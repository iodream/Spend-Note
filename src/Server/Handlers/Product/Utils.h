#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../Entities/Entities.h"

db::Product ToDBProduct(const Product& product);

Product ToNetProduct(const db::Product& db_product, const db::ProductCategory& category);

ProductCategory ToNetProductCategory(const db::ProductCategory& db_product_category);
