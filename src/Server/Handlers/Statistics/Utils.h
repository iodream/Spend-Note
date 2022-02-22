#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../Entities/Entities.h"

ExpensePerCategory ToNetExpensePerCategory(const db::ExpensePerCategory& db_expense);

ExpensePercentagePerCategory ToNetExpensePercentagePerCategory(const db::ExpensePercentagePerCategory& db_expense);

ExpensePerDay ToNetExpensePerDay(const db::ExpensePerDay& db_expense);
