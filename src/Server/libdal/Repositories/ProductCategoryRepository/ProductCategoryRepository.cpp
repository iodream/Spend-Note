#include "ProductCategoryRepository.h"

#include <algorithm>
#include "Exceptions/DatabaseFailure.h"
#include "DatabaseNames.h"

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
				db::productCategory::ID + ", " +
				db::productCategory::NAME +
			" FROM " + db::productCategory::TABLE_NAME +
			" WHERE " + db::productCategory::ID + " = " + w.quote(id) + ";");

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
				db::productCategory::ID + ", " +
				db::productCategory::NAME +
			" FROM " + db::productCategory::TABLE_NAME + ";");

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
	product_category.id = row[db::productCategory::ID].as<IdType>();
	product_category.name = row[db::productCategory::NAME].as<std::string>();
	return product_category;
}
