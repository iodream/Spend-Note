#include "ProductCustomCategoryRepository.h"

#include <algorithm>
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"
#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

ProductCustomCategoryRepository::ProductCustomCategoryRepository(pqxx::connection& db_connection)
	: m_database_connection(db_connection)
{

}

std::optional<ProductCustomCategory> ProductCustomCategoryRepository::GetById(IdType id, IdType user_id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_category_rows = w.exec(
			"SELECT " +
				db::productCustomCategory::ID + ", " +
				db::productCustomCategory::NAME +
			" FROM " + db::productCustomCategory::TABLE_NAME +
			" WHERE " + db::productCustomCategory::ID + " = " + w.quote(id) +
			" AND " + db::productCustomCategory::USER_ID + " = " + w.quote(user_id) + ";");

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

std::vector<ProductCustomCategory> ProductCustomCategoryRepository::GetAll(IdType user_id)
{
	std::vector<ProductCustomCategory> product_categories;

	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_category_rows = w.exec(
			"SELECT " +
				db::productCustomCategory::ID + ", " +
				db::productCustomCategory::NAME +
			" FROM " + db::productCustomCategory::TABLE_NAME +
			" WHERE " + db::productCustomCategory::USER_ID + " = " + w.quote(user_id) + ";");

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

std::optional<IdType> ProductCustomCategoryRepository::Add(const ProductCustomCategory &category)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " + db::productCustomCategory::TABLE_NAME + " (" +
				db::productCustomCategory::NAME + ", " +
				db::productCustomCategory::USER_ID + ") " +
			"VALUES (" +
				w.quote(category.name) + ", " +
				w.quote(category.user_id) + ") " +
			"RETURNING " + db::productCustomCategory::ID + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[db::productCustomCategory::ID].as<IdType>();
	}
	catch (const pqxx::sql_error& e)
	{
		throw SQLFailure(e.what());
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return std::nullopt;
}

bool ProductCustomCategoryRepository::Update(const ProductCustomCategory &category)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::productCustomCategory::ID +
							 " FROM " + db::productCustomCategory::TABLE_NAME +
							 " WHERE " + db::productCustomCategory::ID + " = " + w.quote(category.id) +
							 " AND " + db::productCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0(
				"UPDATE " + db::productCustomCategory::TABLE_NAME +
				" SET " +
					db::productCustomCategory::NAME + " = " + w.quote(category.name) +
				" WHERE " +
					db::productCustomCategory::ID + " = " + w.quote(category.id) +
				" AND " +
					db::productCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";"

				);
		w.commit();
	}
	catch (const pqxx::failure& e)
	{
		throw  DatabaseFailure(e.what());
	}
	return true;
}


bool ProductCustomCategoryRepository::Remove(const ProductCustomCategory &category)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::productCustomCategory::ID +
							 " FROM " + db::productCustomCategory::TABLE_NAME +
							 " WHERE " + db::productCustomCategory::ID + " = " + w.quote(category.id) +
							 " AND " + db::productCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0("DELETE FROM " + db::productCustomCategory::TABLE_NAME +
				" WHERE " + db::productCustomCategory::ID + " = " + w.quote(category.id) +
				" AND " + db::productCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";");

		w.commit();
	}
	catch (const pqxx::sql_error& e)
	{
		throw SQLFailure(e.what());
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

ProductCustomCategory ProductCustomCategoryRepository::ProductCategoryFromRow(const pqxx::row& row)
{
	ProductCustomCategory product_category;
	product_category.id = row[db::productCustomCategory::ID].as<IdType>();
	product_category.user_id = row[db::productCustomCategory::USER_ID].as<IdType>();
	product_category.name = row[db::productCustomCategory::NAME].as<std::string>();
	return product_category;
}

}
