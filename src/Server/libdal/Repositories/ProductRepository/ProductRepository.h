#pragma once

#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "DTOs/Product.h"

namespace db
{
class ProductRepository
{
public:
	ProductRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const Product& product);
	std::optional<Product> GetById(IdType id);
	std::vector<Product> GetByListId(IdType list_id);
	std::vector<Product> GetDailyList(IdType user_id);
	std::vector<Product> GetByPeriodicProductId(IdType periodic_id);

	bool Update(const Product& product);
	bool Remove(IdType id);

	bool CanUserEditProduct(IdType user_id, IdType product_id);
private:
	static Product ProductFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
