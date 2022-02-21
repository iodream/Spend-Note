#include "IncomeRepository.h"

#include "Exceptions/NonexistentResource.h"
#include "DatabaseNames.h"

namespace db
{

IncomeRepository::IncomeRepository(pqxx::connection& db_connection) : m_db_connection(db_connection)
{
}

std::optional<IdType> IncomeRepository::Add(const Income& income)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto id_rows = w.exec(
			"INSERT INTO " + db::income::TABLE_NAME + " (" +
			db::income::USER_ID + ", " +
			db::income::NAME + ", " +
			db::income::AMOUNT + ", " +
			db::income::CATEGORY_ID + ", " +
			db::income::ADD_TIME + ", " +
			db::income::EXPIRATION_TIME+ ") " +
			"VALUES (" +
			w.quote(income.user_id) + ", " +
			w.quote(income.name)+ ", " +
			w.quote(income.amount) + ", " 	+
			w.quote(income.category_id) + ", " 	+
			w.quote(income.add_time) + ", " +
			w.quote(income.expiration_time) + ")" +
			" RETURNING " + db::income::ID + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[db::income::ID].as<IdType>();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}

std::optional<Income> IncomeRepository::GetIncome(const IdType& income_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		pqxx::result income = w.exec(
			"SELECT * FROM " + db::income::TABLE_NAME +
			" WHERE " + db::income::ID + " = "  + w.quote(income_id) + ";");

		if(!income.empty())
		{
			return ParseSQLRow(income.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return std::nullopt;
}

bool IncomeRepository::Update(const Income& income)
{
	try
	{
		pqxx::work w{m_db_connection};

		auto result = w.exec(
			"SELECT " + db::income::ID +
			" FROM  " + db::income::TABLE_NAME +
			" WHERE " + db::income::ID + " = " + w.quote(income.id));

		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + db::income::TABLE_NAME +
			" SET " +
				db::income::NAME + " = " + w.quote(income.name) + ", " +
				db::income::AMOUNT + " = " + w.quote(income.amount) + ", " +
				db::income::CATEGORY_ID + " = " + w.quote(income.category_id) + ", " +
				db::income::ADD_TIME + " = " + w.quote(income.add_time) + ", " +
				db::income::EXPIRATION_TIME + " = " + w.quote(income.expiration_time) +
			" WHERE " +
				db::income::ID + " = " + w.quote(income.id) + ";");

		w.commit();

	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool IncomeRepository::Remove(const IdType& id)
{
	try
	{
		pqxx::work w{m_db_connection};
		auto result = w.exec(
			"SELECT " + db::income::ID +
			" FROM  " + db::income::TABLE_NAME +
			" WHERE " + db::income::ID + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}
		w.exec0(
			"DELETE FROM " + db::income::TABLE_NAME +
			" WHERE " + db::income::ID + " = " + w.quote(id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool IncomeRepository::CanUserEditIncome(IdType user_id, IdType income_id)
{
	try
	{
		pqxx::nontransaction w{m_db_connection};

		auto result = w.exec(
			"SELECT " + db::income::ID +
			" FROM " + db::income::TABLE_NAME +
			" WHERE " +
				db::income::ID +" = "  + w.quote(income_id) + " AND " +
				db::income::USER_ID +" = "  + w.quote(user_id));

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

std::vector<Income> IncomeRepository::GetAllIncomes(const IdType &user_id)
{
	try
	{
		pqxx::work w{m_db_connection};
		std::vector<Income> incomes;

		pqxx::result user_ids = w.exec(
			"SELECT " + db::user::ID +
			" FROM " + db::user::TABLE_NAME +
			" WHERE " + db::user::ID + " = " + w.quote(user_id) + ";");
		if (user_ids.empty())
		{
			auto message = "User with id = " + std::to_string(user_id) + " not found";
			throw NonexistentResource(message);
		}

		pqxx::result r = w.exec(
			"SELECT * FROM " + db::income::TABLE_NAME +
			" WHERE " + db::income::USER_ID + " = " + w.quote(user_id) + ";");

		for(const auto& row : r)
		{
			incomes.push_back(ParseSQLRow(row));
		}
		return incomes;
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
}


Income IncomeRepository::ParseSQLRow(const pqxx::row &row)
{
	Income income;

	income.id = row[db::income::ID].as<IdType>();
	income.user_id = row[db::income::USER_ID].as<IdType>();
	income.name = row[db::income::NAME].as<std::string>();
	income.amount = row[db::income::AMOUNT].as<Money>();
	income.category_id = row[db::income::CATEGORY_ID].as<IdType>();
	income.add_time = row[db::income::ADD_TIME].as<Timestamp>();
	income.expiration_time = row[db::income::EXPIRATION_TIME].get<Timestamp>();

	return income;
}
}
