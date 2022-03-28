#pragma once

#include <pqxx/pqxx>
#include "DTOs/ProductCustomCategory.h"

namespace db
{
class ProductCustomCategoryRepository
{
public:
	ProductCustomCategoryRepository(pqxx::connection& db_connection);

	std::optional<ProductCustomCategory> GetById(IdType id, IdType user_id);
	std::vector<ProductCustomCategory> GetAll(IdType user_id);
	std::optional<IdType> Add(const ProductCustomCategory& category);
	bool Update(const ProductCustomCategory& category);
	bool Remove(const ProductCustomCategory& category);

private:
	static ProductCustomCategory ProductCategoryFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
