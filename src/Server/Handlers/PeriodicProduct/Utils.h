#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../Entities/Entities.h"

db::PeriodicProduct ToDBPeriodicProduct(const PeriodicProduct& product);

PeriodicProduct ToNetPeriodicProduct(const db::PeriodicProduct& db_product, const db::ProductCategory& category);
