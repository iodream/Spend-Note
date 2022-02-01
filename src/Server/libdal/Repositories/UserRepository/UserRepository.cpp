#include "UserRepository.h"
#include "Exceptions/DatabaseFailure.h"
#include <iostream>

namespace
{
	const std::string TABLE_NAME = "User_";
	const std::string ID_FIELD = "id";
	const std::string LOGIN_FIELD = "login";
	const std::string PASSWORD_FIELD = "password";
}

UserRepository::UserRepository(pqxx::connection &db_connection) : m_database_connection(db_connection)
{

}

std::optional<IdType> UserRepository::Add(const User &user)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto id_rows = w.exec(
			"INSERT INTO " + TABLE_NAME + " (" +
				LOGIN_FIELD + ", " +
				PASSWORD_FIELD +
			") VALUES (" +
				w.quote(user.login) + ", " +
				w.quote(user.password) + ")" +
			" RETURNING " + ID_FIELD + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[ID_FIELD].as<IdType>();
	}

	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::optional<User> UserRepository::GetById(IdType id)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result user_rows = w.exec(
			"SELECT " + ID_FIELD + ", " + LOGIN_FIELD + ", " + PASSWORD_FIELD +
			" FROM " + TABLE_NAME +
			" WHERE " + ID_FIELD + " = " + w.quote(id) + ";");

		if (!user_rows.empty())
		{
			return UserFromRow(user_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

std::optional<User> UserRepository::GetByLogin(const std::string& login)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result user_rows = w.exec(
			"SELECT " + ID_FIELD + ", " + LOGIN_FIELD + ", " + PASSWORD_FIELD +
			" FROM " + TABLE_NAME +
			" WHERE " + LOGIN_FIELD + " = " + w.quote(login) + ";");

		if (!user_rows.empty())
		{
			return UserFromRow(user_rows.front());
		}
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}

	return std::nullopt;
}

bool UserRepository::Update(const User &user)
{
	try
	{
		pqxx::work w(m_database_connection);

		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(user.id));
		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + TABLE_NAME +
			" SET " +
				LOGIN_FIELD + " = " + w.quote(user.login) + ", " +
				PASSWORD_FIELD + " = " + w.quote(user.password) +
			" WHERE " + ID_FIELD + " = " + w.quote(user.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool UserRepository::Remove(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto result = w.exec("SELECT " + ID_FIELD + " FROM  " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

User UserRepository::UserFromRow(const pqxx::row& row)
{
	User user;
	user.id = row[ID_FIELD].as<int>();
	user.login = row[LOGIN_FIELD].as<std::string>();
	user.password = row[PASSWORD_FIELD].as<std::string>();
	return user;
}
