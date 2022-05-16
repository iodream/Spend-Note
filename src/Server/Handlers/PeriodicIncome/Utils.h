#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../Entities/Entities.h"

db::PeriodicIncome ToDBPeriodicIncome(const PeriodicIncome& income, const IdType& user_id);

PeriodicIncome ToNetPeriodicIncome(const db::PeriodicIncome& db_income, const db::IncomeCategory& category);
