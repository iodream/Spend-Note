#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../../Entities/Entities.h"

::IncomeCategory ToNetIncomeCategory(const db::IncomeCategory& db_income_category);

db::IncomeCategory ToDBIncomeCategory(const IncomeCategory& category, const IdType& user_id);
