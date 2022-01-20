#pragma once

#include "pqxx/pqxx"

#include "DTOs/ListState.h"
#include "Types.h"
#include "Exceptions/databasefailure.h"

class ListStateRepository
{
public:
    ListStateRepository(pqxx::connection& db_connection);

    std::optional<ListState> GetById(const idType& list_state_id);
    std::vector<ListState> GetAll();

private:
    pqxx::connection& m_db_connection;

    ListState ParseSQLRow(const pqxx::row& row);
};
