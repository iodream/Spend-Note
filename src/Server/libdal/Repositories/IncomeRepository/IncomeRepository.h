#pragma once

#include <pqxx/pqxx>

#include "DTOs/Income.h"
#include "Exceptions/databasefailure.h"

class IncomeRepository
{
public:
    IncomeRepository(pqxx::connection& db_connection);

    void Add(const Income& income);
    std::optional<Income> GetIncome(const idType& income_id);
    std::optional<std::vector<Income>> GetAllIncomes(const idType& user_id);
    void Update(const Income& income);
    void Remove(const idType& income_id);


private:
    pqxx::connection& m_db_connection;

    Income ParseSQLRow(const pqxx::row& row);
};
