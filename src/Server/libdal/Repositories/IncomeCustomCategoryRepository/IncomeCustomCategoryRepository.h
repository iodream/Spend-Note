#pragma once

#include <pqxx/pqxx>
#include "DTOs/IncomeCustomCategory.h"

namespace db
{
class IncomeCustomCategoryRepository
{
public:
	IncomeCustomCategoryRepository(pqxx::connection& db_connection);

	std::optional<IncomeCustomCategory> GetById(IdType id, IdType user_id);
	std::vector<IncomeCustomCategory> GetAll(IdType user_id);
	std::optional<IdType> Add(const IncomeCustomCategory& category);
	bool Update(const IncomeCustomCategory& category);
	bool Remove(const IncomeCustomCategory& category);

private:
	static IncomeCustomCategory IncomeCategoryFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
