#include <DTOs/List.h>

#include <pqxx/pqxx>
#include <chrono>

#include "Exceptions/databasefailure.h"

class ListRepository
{
public:
    ListRepository(pqxx::connection& database_connection);

    void AddList(const List& list_);
    std::optional<List> GetList(const idType& id);
    void Update(const List& list_);
    void Remuve(const idType& id);

private:
    pqxx::connection& m_database_connection;
};
