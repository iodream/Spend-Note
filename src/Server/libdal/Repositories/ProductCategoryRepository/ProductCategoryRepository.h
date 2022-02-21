#pragma once

#include <pqxx/pqxx>
#include "DTOs/ProductCategory.h"

namespace db
{
class ProductCategoryRepository
{
public:
	ProductCategoryRepository(pqxx::connection& db_connection);

	std::optional<ProductCategory> GetById(IdType id);
	std::vector<ProductCategory> GetAll();
private:
	static ProductCategory ProductCategoryFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
