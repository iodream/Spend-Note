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
	std::vector<ProductCategory> GetAll(IdType user_id);
	std::optional<IdType> Add(const ProductCategory& category);
	bool Update(const ProductCategory& category);
	bool Remove(const ProductCategory& category);
	bool CanUserEditProductCategory(IdType user_id, IdType category_id);

private:
	static ProductCategory ProductCategoryFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
