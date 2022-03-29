#include "IncomeCustomCategoryRepository.h"

#include <algorithm>
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"
#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

IncomeCustomCategoryRepository::IncomeCustomCategoryRepository(pqxx::connection& db_connection)
	: m_database_connection(db_connection)
{

}

std::optional<IncomeCustomCategory> IncomeCustomCategoryRepository::GetById(IdType id, IdType user_id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result income_category_rows = w.exec(
			"SELECT * FROM " + db::incomeCustomCategory::TABLE_NAME +
			" WHERE " + db::incomeCustomCategory::ID + " = " + w.quote(id) +
			" AND " + db::incomeCustomCategory::USER_ID + " = " + w.quote(user_id) + ";");

		if (!income_category_rows.empty())
		{
			return IncomeCategoryFromRow(income_category_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::vector<IncomeCustomCategory> IncomeCustomCategoryRepository::GetAll(IdType user_id)
{
	std::vector<IncomeCustomCategory> income_categories;

	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result income_category_rows = w.exec(
			"SELECT * FROM " + db::incomeCustomCategory::TABLE_NAME +
			" WHERE " + db::incomeCustomCategory::USER_ID + " = " + w.quote(user_id) + ";");

		income_categories.resize(income_category_rows.size());
		std::transform(
			income_category_rows.cbegin(),
			income_category_rows.cend(),
			income_categories.begin(),
			IncomeCategoryFromRow);
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return income_categories;
}

std::optional<IdType> IncomeCustomCategoryRepository::Add(const IncomeCustomCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " +
				db::incomeCustomCategory::TABLE_NAME + " (" +
				db::incomeCustomCategory::NAME + ", " +
				db::incomeCustomCategory::USER_ID + ") " +
			"VALUES (" +
				w.quote(category.name) + ", " +
				w.quote(category.user_id) + ") " +
			"RETURNING " + db::incomeCustomCategory::ID + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[db::incomeCustomCategory::ID].as<IdType>();
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

bool IncomeCustomCategoryRepository::Update(const IncomeCustomCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::incomeCustomCategory::ID +
							 " FROM " + db::incomeCustomCategory::TABLE_NAME +
							 " WHERE " + db::incomeCustomCategory::ID + " = " + w.quote(category.id) +
							 " AND " + db::incomeCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0(
				"UPDATE " + db::incomeCustomCategory::TABLE_NAME +
				" SET " +
					db::incomeCustomCategory::NAME + " = " + w.quote(category.name) +
				" WHERE " +
					db::incomeCustomCategory::ID + " = " + w.quote(category.id) +
				" AND " +
					db::incomeCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";"

				);
		w.commit();
	}
	catch (const pqxx::failure& e)
	{
		throw  DatabaseFailure(e.what());
	}
	return true;
}


bool IncomeCustomCategoryRepository::Remove(const IncomeCustomCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + db::incomeCustomCategory::ID +
							 " FROM " + db::incomeCustomCategory::TABLE_NAME +
							 " WHERE " + db::incomeCustomCategory::ID + " = " + w.quote(category.id) +
							 " AND " + db::incomeCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0("DELETE FROM " + db::incomeCustomCategory::TABLE_NAME +
				" WHERE " + db::incomeCustomCategory::ID + " = " + w.quote(category.id) +
				" AND " + db::incomeCustomCategory::USER_ID + " = " + w.quote(category.user_id) + ";");

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

IncomeCustomCategory IncomeCustomCategoryRepository::IncomeCategoryFromRow(const pqxx::row& row)
{
	IncomeCustomCategory income_category;
	income_category.id = row[db::incomeCustomCategory::ID].as<IdType>();
	income_category.user_id = row[db::incomeCustomCategory::USER_ID].as<IdType>();
	income_category.name = row[db::incomeCustomCategory::NAME].as<std::string>();
	return income_category;
}

}
