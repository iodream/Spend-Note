#pragma once

#include "../libdal/Facade/IDbFacade.h"
#include "../Entities/Entities.h"

ExpensePerCategory ToNetExpensePerCategory(const db::ExpensePerCategory& db_expense);
