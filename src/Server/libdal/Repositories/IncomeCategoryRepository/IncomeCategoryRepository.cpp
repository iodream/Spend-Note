#include "IncomeCategoryRepository.h"

namespace db
{

namespace
{
	const std::string& TABLE_NAME = "IncomeCategory";
	const std::string& ID_FIELD = "id";
	const std::string& NAME_FIELD = "name";
}

IncomeCategoryRepository::IncomeCategoryRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

std::optional<IncomeCategory> IncomeCategoryRepository::GetById(const IdType& category_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::result income_category = w.exec("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(category_id) + ";");

		return ParseSQLRow(income_category.front());
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return std::nullopt;
}

IncomeCategory IncomeCategoryRepository::ParseSQLRow(const pqxx::row& row)
{
	IncomeCategory income_category;

	income_category.id = row[ID_FIELD].as<IdType>();
	income_category.name = row[NAME_FIELD].as<std::string>();

	return income_category;
}

std::vector<IncomeCategory> IncomeCategoryRepository::GetAll()
{
	try
	{
		pqxx::work w{m_db_connection};
		std::vector<IncomeCategory> income_categories;

		pqxx::result r = w.exec("SELECT * FROM " + TABLE_NAME + ";");

		for(const auto& row : r)
		{
			income_categories.push_back(ParseSQLRow(row));
		}
		return income_categories;
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

}
