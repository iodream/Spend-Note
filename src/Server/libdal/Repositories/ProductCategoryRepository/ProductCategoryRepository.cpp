#include "ProductCategoryRepository.h"

#include <algorithm>
#include "Exceptions/DatabaseFailure.h"

namespace db
{

namespace
{
	const std::string TABLE_NAME = "ProductCategory";
	const std::string ID_FIELD = "id";
	const std::string NAME_FIELD = "name";
}

ProductCategoryRepository::ProductCategoryRepository(pqxx::connection& db_connection) : m_database_connection(db_connection)
{

}

std::optional<ProductCategory> ProductCategoryRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_category_rows = w.exec(
			"SELECT " +
				ID_FIELD + ", " +
				NAME_FIELD +
			" FROM " + TABLE_NAME +
			" WHERE " + ID_FIELD + " = " + w.quote(id) + ";");

		if (!product_category_rows.empty())
		{
			return ProductCategoryFromRow(product_category_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::vector<ProductCategory> ProductCategoryRepository::GetAll()
{
	std::vector<ProductCategory> product_categories;

	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_category_rows = w.exec(
			"SELECT " +
				ID_FIELD + ", " +
				NAME_FIELD +
			" FROM " + TABLE_NAME + ";");

		product_categories.resize(product_category_rows.size());
		std::transform(
				product_category_rows.cbegin(),
				product_category_rows.cend(),
				product_categories.begin(),
				ProductCategoryFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return product_categories;
}

ProductCategory ProductCategoryRepository::ProductCategoryFromRow(const pqxx::row& row)
{
	ProductCategory product_category;
	product_category.id = row[ID_FIELD].as<IdType>();
	product_category.name = row[NAME_FIELD].as<std::string>();
	return product_category;
}

}
