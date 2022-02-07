#pragma once

#include <pqxx/pqxx>

#include "DTOs/Income.h"
#include "Exceptions/DatabaseFailure.h"

namespace db
{
class IncomeRepository
{
public:
	IncomeRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const Income& income);
	std::optional<Income> GetIncome(const IdType& income_id);
	std::vector<Income> GetAllIncomes(const IdType& user_id);
	bool Update(const Income& income);
	bool Remove(const IdType& income_id);

private:
	pqxx::connection& m_db_connection;

	Income ParseSQLRow(const pqxx::row& row);
};
}
