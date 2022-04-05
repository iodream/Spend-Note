#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../../Entities/Entities.h"

ProductCategory ToNetProductCategory(const db::ProductCategory& db_product_category);

db::ProductCategory ToDBProductCategory(const ProductCategory& category, const IdType& user_id);
