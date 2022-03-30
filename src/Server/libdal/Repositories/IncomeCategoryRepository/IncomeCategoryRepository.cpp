#include "IncomeCategoryRepository.h"

#include <algorithm>
#include "Exceptions/DatabaseFailure.h"
#include "Exceptions/SQLFailure.h"
#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

IncomeCategoryRepository::IncomeCategoryRepository(pqxx::connection& db_connection)
	: m_database_connection(db_connection)
{

}

std::optional<IncomeCategory> IncomeCategoryRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result income_category_rows = w.exec(
			"SELECT " +
				db::incomeCategory::ID + ", " +
				db::incomeCategory::NAME + ", " +
				db::incomeCategory::USER_ID  +
			" FROM " + db::incomeCategory::TABLE_NAME +
			" WHERE " + db::incomeCategory::ID + " = " + w.quote(id) + ";");

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

std::vector<IncomeCategory> IncomeCategoryRepository::GetAll(IdType user_id)
{
	std::vector<IncomeCategory> income_categories;

	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result income_category_rows = w.exec(
			"SELECT " +
				db::incomeCategory::ID + ", " +
				db::incomeCategory::NAME + ", " +
				db::incomeCategory::USER_ID  +
			" FROM " + db::incomeCategory::TABLE_NAME +
			" WHERE " + db::incomeCategory::USER_ID + " = " + w.quote(user_id) + ";");

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

std::optional<IdType> IncomeCategoryRepository::Add(const IncomeCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		pqxx::result id_rows = w.exec(
			"INSERT INTO " +
				db::incomeCategory::TABLE_NAME + " (" +
				db::incomeCategory::NAME + ", " +
				db::incomeCategory::USER_ID + ") " +
			"VALUES (" +
				w.quote(category.name) + ", " +
				w.quote(category.user_id) + ") " +
			"RETURNING " + db::incomeCategory::ID + ";");
		w.commit();
		auto id_row = id_rows.front();
		return id_row[db::incomeCategory::ID].as<IdType>();
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

bool IncomeCategoryRepository::Update(const IncomeCategory& category)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + db::incomeCategory::ID +
			 " FROM " + db::incomeCategory::TABLE_NAME +
			 " WHERE " + db::incomeCategory::ID + " = " + w.quote(category.id) +
			 " AND " + db::incomeCategory::USER_ID + " = " + w.quote(category.user_id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + db::incomeCategory::TABLE_NAME +
			" SET " +
			db::incomeCategory::NAME + " = " + w.quote(category.name) +
			" WHERE " +
			db::incomeCategory::ID + " = " + w.quote(category.id) +
			" AND " +
			db::incomeCategory::USER_ID + " = " + w.quote(category.user_id) + ";"

				);
		w.commit();
	}
	catch (const pqxx::failure& e)
	{
		throw  DatabaseFailure(e.what());
	}
	return true;
}


bool IncomeCategoryRepository::Remove(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec(
			"SELECT " + db::incomeCategory::ID +
			" FROM " + db::incomeCategory::TABLE_NAME +
			" WHERE " + db::incomeCategory::ID + " = " + w.quote(id) + ";");
		if(result.empty())
		{
			return false;
		}

		w.exec0(
			"DELETE FROM " + db::incomeCategory::TABLE_NAME +
			" WHERE " + db::incomeCategory::ID + " = " + w.quote(id) + ";");

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

bool IncomeCategoryRepository::CanUserEditIncomeCategory(IdType user_id, IdType income_id)
{
	try
	{
		pqxx::nontransaction w{m_database_connection};

		auto result = w.exec(
			"SELECT " + db::incomeCategory::ID +
			" FROM " + db::incomeCategory::TABLE_NAME +
			" WHERE " +
				db::incomeCategory::ID +" = "  + w.quote(income_id) + " AND " +
				db::incomeCategory::USER_ID +" = "  + w.quote(user_id));

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

IncomeCategory IncomeCategoryRepository::IncomeCategoryFromRow(const pqxx::row& row)
{
	IncomeCategory income_category;
	income_category.id = row[db::incomeCategory::ID].as<IdType>();
	income_category.user_id = row[db::incomeCategory::USER_ID].as<IdType>();
	income_category.name = row[db::incomeCategory::NAME].as<std::string>();
	return income_category;
}

}
