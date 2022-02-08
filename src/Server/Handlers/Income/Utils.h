#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../Entities/Entities.h"

db::Income ToDBIncome(const Income& income);

Income ToNetIncome(const db::Income& db_income, const db::IncomeCategory& category);
