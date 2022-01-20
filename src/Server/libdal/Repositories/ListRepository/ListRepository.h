#include <DTOs/List.h>

#include <pqxx/pqxx>
#include <chrono>

#include "Exceptions/databasefailure.h"

class ListRepository
{
public:
    ListRepository(pqxx::connection& db_connection);

	void AddList(const List& list);
	std::optional<List> GetList(const idType& list_id);
	std::optional<std::vector<List>> GetAllLists(const idType& user_id);
	void Update(const List& list);
	void Remove(const idType& list_id);

private:
    List ParseSQLRow(const pqxx::row& row);
    pqxx::connection& m_db_connection;
};
