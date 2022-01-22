#pragma once

#include <pqxx/pqxx>

#include "DTOs/Income.h"
#include "Exceptions/DatabaseFailure.h"

class IncomeRepository
{
public:
	IncomeRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const Income& income);
	std::optional<Income> GetIncome(const IdType& income_id);
	std::optional<std::vector<Income>> GetAllIncomes(const IdType& user_id);
	void Update(const Income& income);
	void Remove(const IdType& income_id);


private:
	pqxx::connection& m_db_connection;

	Income ParseSQLRow(const pqxx::row& row);
};
