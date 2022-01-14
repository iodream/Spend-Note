#pragma once

#include <pqxx/pqxx>

#include "DTOs/Income.h"
#include "Exceptions/databasefailure.h"

class IncomeRepository
{
public:
    IncomeRepository(pqxx::connection& databaseConnection);

    void Add(const Income& income);
    std::optional<Income> GetIncome(const idType& id);
    void Update(const Income& income);
    void Remuve(const idType& id);

private:
    pqxx::connection& m_databaseConnection;
};
