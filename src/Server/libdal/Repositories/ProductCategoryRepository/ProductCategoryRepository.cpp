#include "ProductCategoryRepository.h"

#include <algorithm>
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"
#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

ProductCategoryRepository::ProductCategoryRepository(pqxx::connection& db_connection)
	: m_database_connection(db_connection)
{

}

std::optional<ProductCategory> ProductCategoryRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_category_rows = w.exec(
			"SELECT * FROM " + db::productCategory::TABLE_NAME +
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

std::vector<ProductCategory> ProductCategoryRepository::GetAll(IdType user_id)
{
	std::vector<ProductCategory> product_categories;

	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result product_category_rows = w.exec(
			"SELECT * FROM " + db::productCategory::TABLE_NAME +
			" WHERE " + db::productCategory::USER_ID + " = " + w.quote(user_id) + ";");

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

std::optional<IdType> ProductCategoryRepository::Add(const ProductCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " +
				db::productCategory::TABLE_NAME + " (" +
				db::productCategory::NAME + ", " +
				db::productCategory::USER_ID + ") " +
			"VALUES (" +
				w.quote(category.name) + ", " +
				w.quote(category.user_id) + ") " +
			"RETURNING " + db::productCategory::ID + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[db::productCategory::ID].as<IdType>();
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

bool ProductCategoryRepository::Update(const ProductCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::productCategory::ID +
				" FROM " + db::productCategory::TABLE_NAME +
				" WHERE " + db::productCategory::ID + " = " + w.quote(category.id) +
				" AND " + db::productCategory::USER_ID + " = " + w.quote(category.user_id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0(
				"UPDATE " + db::productCategory::TABLE_NAME +
				" SET " +
					db::productCategory::NAME + " = " + w.quote(category.name) +
				" WHERE " +
					db::productCategory::ID + " = " + w.quote(category.id) +
				" AND " +
					db::productCategory::USER_ID + " = " + w.quote(category.user_id) + ";"

				);
		w.commit();
	}
	catch (const pqxx::failure& e)
	{
		throw  DatabaseFailure(e.what());
	}
	return true;
}


bool ProductCategoryRepository::Remove(const ProductCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::productCategory::ID +
				" FROM " + db::productCategory::TABLE_NAME +
				" WHERE " + db::productCategory::ID + " = " + w.quote(category.id) +
				" AND " + db::productCategory::USER_ID + " = " + w.quote(category.user_id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0("DELETE FROM " + db::productCategory::TABLE_NAME +
				" WHERE " + db::productCategory::ID + " = " + w.quote(category.id) +
				" AND " + db::productCategory::USER_ID + " = " + w.quote(category.user_id) + ";");

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

bool ProductCategoryRepository::CanUserEditProductCategory(IdType user_id, IdType category_id)
{
	try
	{
		pqxx::nontransaction w{m_database_connection};

		auto result = w.exec(
			"SELECT " + db::productCategory::ID +
			" FROM " + db::productCategory::TABLE_NAME +
			" WHERE " +
				db::productCategory::ID +" = "  + w.quote(category_id) + " AND " +
				db::productCategory::USER_ID +" = "  + w.quote(user_id));

		if (result.empty())
		{
			return false;
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return true;
}


ProductCategory ProductCategoryRepository::ProductCategoryFromRow(const pqxx::row& row)
{
	ProductCategory product_category;
	product_category.id = row[db::productCategory::ID].as<IdType>();
	product_category.name = row[db::productCategory::NAME].as<std::string>();
	product_category.user_id = row[db::productCategory::USER_ID].as<IdType>();
	return product_category;
}

}
