#include "userrepository.h"
#include "Exceptions/databasefailure.h"

namespace
{
	const std::string& TABLE_NAME = "User_";
	const std::string& ID_FIELD = "id";
	const std::string& LOGIN_FIELD = "login";
	const std::string& PASSWORD_FIELD = "password";
}

UserRepository::UserRepository(pqxx::connection &db_connection) : m_database_connection(db_connection)
{

}

void UserRepository::Add(const User &user)
{
	pqxx::work w(m_database_connection);
	try
	{
		w.exec0(
			"INSERT INTO " + TABLE_NAME + " (" +
				LOGIN_FIELD + ", " +
				PASSWORD_FIELD +
			") VALUES (" +
				w.quote(user.login) + ", " +
				w.quote(user.password) + ");");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

std::optional<User> UserRepository::GetById(IdType id)
{
	pqxx::nontransaction w(m_database_connection);

	try
	{
		pqxx::result user_rows = w.exec(
			"SELECT " + ID_FIELD + ", " + LOGIN_FIELD + ", " + PASSWORD_FIELD +
			" FROM " + TABLE_NAME +
			" WHERE " + ID_FIELD + " = " + w.quote(id) + ";");

		if (!user_rows.empty())
		{
			return UserFromRow(user_rows.front());
		}
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}

	return std::nullopt;
}

std::optional<User> UserRepository::GetByLogin(const std::string& login)
{
	pqxx::nontransaction w(m_database_connection);

	try
	{
		pqxx::result user_rows = w.exec(
			"SELECT " + ID_FIELD + ", " + LOGIN_FIELD + ", " + PASSWORD_FIELD +
			" FROM " + TABLE_NAME +
			" WHERE " + LOGIN_FIELD + " = " + w.quote(login) + ";");

		if (!user_rows.empty())
		{
			return UserFromRow(user_rows.front());
		}
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}

	return std::nullopt;
}

void UserRepository::Update(const User &user)
{
	pqxx::work w(m_database_connection);

	try
	{
		w.exec0(
			"UPDATE " + TABLE_NAME +
			" SET " +
				LOGIN_FIELD + " = " + w.quote(user.login) + ", " +
				PASSWORD_FIELD + " = " + w.quote(user.password) +
			" WHERE " + ID_FIELD + " = " + w.quote(user.id) + ";");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

void UserRepository::Remove(IdType id)
{
	pqxx::work w(m_database_connection);

	try
	{
		w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
		w.commit();
	}
	catch(const pqxx::pqxx_exception& e)
	{
		throw DatabaseFailure();
	}
}

User UserRepository::UserFromRow(const pqxx::row& row)
{
	User user;
	user.id = row[ID_FIELD].as<int>();
	user.login = row[LOGIN_FIELD].as<std::string>();
	user.password = row[PASSWORD_FIELD].as<std::string>();

	return user;
}
