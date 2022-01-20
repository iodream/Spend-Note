#pragma once

#include "pqxx/pqxx"

#include "DTOs/IncomeCategory.h"
#include "Exceptions/databasefailure.h"

class IncomeCategoryRepository
{
public:
    IncomeCategoryRepository(pqxx::connection& db_connection);

    std::optional<IncomeCategory> GetById(const idType& category_id);
    std::vector<IncomeCategory> GetAll();

private:
    pqxx::connection& m_db_connection;

    IncomeCategory ParseSQLRow(const pqxx::row& row);
};
