#pragma once

#include <pqxx/pqxx>
#include "DTOs/IncomeCategory.h"

namespace db
{
class IncomeCategoryRepository
{
public:
	IncomeCategoryRepository(pqxx::connection& db_connection);

	std::optional<IncomeCategory> GetById(IdType id);
	std::vector<IncomeCategory> GetAll(IdType user_id);
	std::optional<IdType> Add(const IncomeCategory& category);
	bool Update(const IncomeCategory& category);
	bool Remove(IdType id);
	bool CanUserEditIncomeCategory(IdType user_id, IdType category_id);

private:
	static IncomeCategory IncomeCategoryFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
