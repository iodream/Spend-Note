#include "IncomeCategoryRepository.h"

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
		pqxx::row income_category = w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(category_id) + ";");

		 return IncomeCategory{income_category[ID_FIELD].as<IdType>(), income_category[NAME_FIELD].as<std::string>()};
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
	return std::nullopt;
}

IncomeCategory IncomeCategoryRepository::ParseSQLRow(const pqxx::row& row)
{
	IncomeCategory income_category;

	income_category.income_category_id = row[ID_FIELD].as<IdType>();
	income_category.name = row[NAME_FIELD].as<std::string>();

	return income_category;
}

std::vector<IncomeCategory> IncomeCategoryRepository::GetAll()
{
	try
	{
		pqxx::work w{m_db_connection};
		std::vector<IncomeCategory> income_categories;

		auto number_of_rows = w.exec("SELECT FROM " + TABLE_NAME + ";");
		pqxx::result r = w.exec_n(number_of_rows.size(), "SELECT * FROM " + TABLE_NAME + ";");

		for(const auto& row : r)
		{
			income_categories.push_back(ParseSQLRow(row));
		}
		return income_categories;
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}
