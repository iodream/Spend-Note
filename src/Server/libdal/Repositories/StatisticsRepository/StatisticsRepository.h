#pragma once

#include <pqxx/pqxx>

#include "Types.h"
#include "DTOs/ProductCategory.h"
#include "DTOs/Statistics.h"

namespace db
{
class StatisticsRepository
{
public:
	StatisticsRepository(pqxx::connection& db_connection);

	std::vector<ExpensePerCategory> ExpensesPerCategory(IdType user_id);
	std::vector<ExpensePercentagePerCategory> ExpensesPercentagePerCategory(IdType user_id);
	std::vector<ExpensePerDay> ExpensesDynamics(IdType user_id);

	std::vector<IncomePerCategory> IncomesPerCategory(IdType user_id);
	std::vector<IncomePercentagePerCategory> IncomesPercentagePerCategory(IdType user_id);
	std::vector<IncomePerDay> IncomesDynamics(IdType user_id);

	static bool DoesUserExist(IdType user_id, pqxx::work& work);
private:
	pqxx::connection& m_db_connection;
};
}
