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
	const std::string& EXPERATION_TIME = "expirationTime";
	const std::string& TABLE_WITH_CATEGORY = "IncomeCategory";
}

IncomeRepository::IncomeRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

void IncomeRepository::Add(const Income& income)
{
	try
	{
		pqxx::work w{m_db_connection};

		w.exec0("INSERT INTO " + TABLE_NAME + " (" + USER_ID + ", " + INCOME_NAME + ", " + AMOUNT + ", "
				+ CATEGORY_ID + ", " + ADD_TIME + ", " + EXPERATION_TIME + ") " +
				"VALUES (" + w.quote(income.user_id) + ", " + w.quote(income.name)+ ", " + w.quote(income.amount) + ", "
				+ w.quote(income.category_id) + ", " + w.quote(income.add_time) + ", "
				+ w.quote(income.expoiration_time) + ");"
				);

		w.commit();

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
		pqxx::row income = w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = "  + w.quote(income_id) + ";");

		if(!income[EXPERATION_TIME].is_null())
		{
			return ParseSQLRow(income);
		}

		else if(income.empty())
			return std::nullopt;

		else
		{
			return ParseSQLRow(income);
		}
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

void IncomeRepository::Update(const Income& income)
{
	try
	{
		pqxx::work w{m_db_connection};
		w.exec0("UPDATE " + TABLE_NAME + " SET " + INCOME_NAME + " = " + w.quote(income.name) + ", "
				+ AMOUNT + " = " + w.quote(income.amount) + ", " + CATEGORY_ID + " = " + w.quote(income.category_id) + ", "
				+ ADD_TIME + " = " + w.quote(income.add_time) + ", " + EXPERATION_TIME + " = " + w.quote(income.expoiration_time)
				+ " WHERE " + ID_FIELD + " = " + w.quote(income.income_id) + ";");
		w.commit();

	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

void IncomeRepository::Remove(const IdType& id)
{
	try
	{
		pqxx::work w{m_db_connection};
		w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

std::optional<std::vector<Income>> IncomeRepository::GetAllIncomes(const IdType &id)
{
	try
	{
		pqxx::work w{m_db_connection};
		std::vector<Income> incomes;

		auto number_of_rows = w.exec("SELECT FROM " + TABLE_NAME + " WHERE " + USER_ID + " = " + w.quote(id) + ";");
		pqxx::result r = w.exec_n(number_of_rows.size(),
								"SELECT * FROM " + TABLE_NAME + " WHERE " + USER_ID + " = " + w.quote(id) + ";");

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
	return std::nullopt;
}


Income IncomeRepository::ParseSQLRow(const pqxx::row &row)
{
	Income income;

	if(!row[EXPERATION_TIME].is_null())
	{
		income.income_id = row[ID_FIELD].as<IdType>();
		income.user_id = row[USER_ID].as<IdType>();
		income.name = row[INCOME_NAME].as<std::string>();
		income.amount = row[AMOUNT].as<double>();
		income.category_id = row[CATEGORY_ID].as<IdType>();
		income.add_time = row[ADD_TIME].as<std::string>();
		income.expoiration_time = row[EXPERATION_TIME].as<std::string>();

		return income;
	}
	else
	{
		income.income_id = row[ID_FIELD].as<IdType>();
		income.user_id = row[USER_ID].as<IdType>();
		income.name = row[INCOME_NAME].as<std::string>();
		income.amount = row[AMOUNT].as<double>();
		income.category_id = row[CATEGORY_ID].as<IdType>();
		income.add_time = row[ADD_TIME].as<std::string>();
		income.expoiration_time = "";

		return income;
	}
}
