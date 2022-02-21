#pragma once

#include <pqxx/pqxx>

#include "Types.h"
#include "DTOs/ProductCategory.h"

namespace db
{
class StatisticsRepository
{
public:
	StatisticsRepository(pqxx::connection& db_connection);

	std::vector<std::pair<IdType, Money>> ExpensesPerCategoryWeekly(IdType user_id); // IdType - product_category_id
	std::vector<std::pair<Date, Money>> ExpencesDynamicsWeekly(IdType user_id);
private:
	pqxx::connection& m_db_connection;
};
}
