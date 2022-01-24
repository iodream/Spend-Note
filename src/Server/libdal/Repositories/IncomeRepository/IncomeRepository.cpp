#include "IncomeRepository.h"
#include <iostream>

namespace
{
	const std::string& TABLE_NAME = "Income";
	const std::string& ID_FIELD = "id";
	const std::string& INCOME_NAME = "name";
	const std::string& USER_ID = "userId";
	const std::string& AMOUNT = "amount";
	const std::string& CATEGORY_ID = "categoryId";
	const std::string& ADD_TIME = "addTime";
	const std::string& EXPIRATION_TIME= "expirationTime";
	const std::string& TABLE_WITH_CATEGORY = "IncomeCategory";
}

IncomeRepository::IncomeRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

std::optional<IdType> IncomeRepository::Add(const Income& income)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto id_rows = w.exec(
				"INSERT INTO " + TABLE_NAME + " (" +
				USER_ID + ", " +
				INCOME_NAME + ", " +
				AMOUNT + ", " +
				CATEGORY_ID + ", " +
				ADD_TIME + ", " +
				EXPIRATION_TIME+ ") " +
				"VALUES (" +
				w.quote(income.user_id) + ", " +
				w.quote(income.name)+ ", " +
				w.quote(income.amount) + ", " 	+
				w.quote(income.category_id) + ", " 	+
				w.quote(income.add_time) + ", " +
				w.quote(income.expiration_time) + ")" +
				" RETURNING " + ID_FIELD + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[ID_FIELD].as<IdType>();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

std::optional<Income> IncomeRepository::GetIncome(const IdType& income_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::result income = w.exec("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = "  + w.quote(income_id) + ";");

		if(!income.empty())
		{
			return ParseSQLRow(income.front());
		}
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
    return std::nullopt;
}

bool IncomeRepository::Update(const Income& income)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(income.income_id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("UPDATE " + TABLE_NAME + " SET " + INCOME_NAME + " = " + w.quote(income.name) + ", "
				+ AMOUNT + " = " + w.quote(income.amount) + ", " + CATEGORY_ID + " = " + w.quote(income.category_id) + ", "
				+ ADD_TIME + " = " + w.quote(income.add_time) + ", " + EXPIRATION_TIME+ " = " + w.quote(income.expiration_time)
				+ " WHERE " + ID_FIELD + " = " + w.quote(income.income_id) + ";");
		w.commit();

	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
	return true;
}

bool IncomeRepository::Remove(const IdType& id)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
	return true;
}

std::vector<Income> IncomeRepository::GetAllIncomes(const IdType &id)
{
	try
	{
		pqxx::work w{m_db_connection};
		std::vector<Income> incomes;

		pqxx::result r = w.exec("SELECT * FROM " + TABLE_NAME + " WHERE " + USER_ID + " = " + w.quote(id) + ";");

		for(const auto& row : r)
		{
			incomes.push_back(ParseSQLRow(row));
		}
		return incomes;
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}


Income IncomeRepository::ParseSQLRow(const pqxx::row &row)
{
	Income income;

    income.income_id = row[ID_FIELD].as<IdType>();
    income.user_id = row[USER_ID].as<IdType>();
    income.name = row[INCOME_NAME].as<std::string>();
    income.amount = row[AMOUNT].as<double>();
    income.category_id = row[CATEGORY_ID].as<IdType>();
    income.add_time = row[ADD_TIME].as<std::string>();
    income.expiration_time = row[EXPIRATION_TIME].get<std::string, std::optional>();

    return income;
}
