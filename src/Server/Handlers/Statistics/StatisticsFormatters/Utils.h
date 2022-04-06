#pragma once

#include "../../../libdal/Facade/IDbFacade.h"
#include "../../Entities/Entities.h"

StatisticPerCategory ToNetStatisticPerCategory(const db::ExpensePerCategory& db_expense);

StatisticPercentagePerCategory ToNetStatisticPercentagePerCategory(const db::ExpensePercentagePerCategory& db_expense);

StatisticPerDay ToNetStatisticPerDay(const db::ExpensePerDay& db_expense);

StatisticPerCategory ToNetStatisticPerCategory(const db::IncomePerCategory& db_income);

StatisticPercentagePerCategory ToNetStatisticPercentagePerCategory(const db::IncomePercentagePerCategory& db_income);

StatisticPerDay ToNetStatisticPerDay(const db::IncomePerDay& db_income);
