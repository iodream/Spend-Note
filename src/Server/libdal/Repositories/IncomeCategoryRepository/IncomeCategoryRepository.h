#pragma once

#include "pqxx/pqxx"

#include "DTOs/IncomeCategory.h"
#include "Exceptions/DatabaseFailure.h"

namespace db
{
class IncomeCategoryRepository
{
public:
	IncomeCategoryRepository(pqxx::connection& db_connection);

	std::optional<IncomeCategory> GetById(const IdType& category_id);
	std::vector<IncomeCategory> GetAll();

private:
	pqxx::connection& m_db_connection;

	IncomeCategory ParseSQLRow(const pqxx::row& row);
};
}
