#pragma once

#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "DTOs/Product.h"

class ProductRepository
{
public:
	ProductRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const Product& product);
	std::optional<Product> GetById(IdType id);
	std::vector<Product> GetByListId(IdType list_id);

	bool Update(const Product& product);
	bool Remove(IdType id);
private:
	static Product ProductFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};

