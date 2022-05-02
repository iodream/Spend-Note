#include "UserRepository.h"

#include <iostream>

#include "Exceptions/DatabaseFailure.h"
#include "DatabaseNames.h"

namespace db
{

UserRepository::UserRepository(pqxx::connection &db_connection) : m_database_connection(db_connection)
{

}

std::optional<IdType> UserRepository::Add(const User &user)
{
	try
	{
		pqxx::work w(m_database_connection);
		auto id_rows = w.exec(
			"INSERT INTO " + db::user::TABLE_NAME + " (" +
				db::user::LOGIN + ", " +
				db::user::PASSWORD + ", " +
				db::user::SALT +
			") VALUES (" +
				w.quote(user.login) + ", " +
				w.quote(user.password_hash) + ", " +
				w.quote(user.salt) + ")" +
			" RETURNING " + db::user::ID + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[db::user::ID].as<IdType>();
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
			"SELECT " + db::user::ID + ", " + db::user::LOGIN + ", " + db::user::PASSWORD + ", " + db::user::SALT +
			" FROM " + db::user::TABLE_NAME +
			" WHERE " + db::user::ID + " = " + w.quote(id) + ";");

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
			"SELECT " + db::user::ID + ", " + db::user::LOGIN + ", " + db::user::PASSWORD + ", " + db::user::SALT +
			" FROM " + db::user::TABLE_NAME +
			" WHERE " + db::user::LOGIN + " = " + w.quote(login) + ";");

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

		auto result = w.exec("SELECT " + db::user::ID + " FROM  " + db::user::TABLE_NAME + " WHERE " + db::user::ID + " = " + w.quote(user.id));
		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + db::user::TABLE_NAME +
			" SET " +
				db::user::LOGIN + " = " + w.quote(user.login) + ", " +
				db::user::PASSWORD + " = " + w.quote(user.password_hash) + ", " +
				db::user::SALT + " = " + w.quote(user.salt) +
			" WHERE " + db::user::ID + " = " + w.quote(user.id) + ";");
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
		auto result = w.exec(
			"SELECT " + db::user::ID +
			" FROM  " + db::user::TABLE_NAME +
			" WHERE " + db::user::ID + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}
		w.exec0("DELETE FROM " + db::user::TABLE_NAME + " WHERE " + db::user::ID + " = " + w.quote(id) + ";");
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
	user.id = row[db::user::ID].as<int>();
	user.login = row[db::user::LOGIN].as<std::string>();
	user.password_hash = row[db::user::PASSWORD].as<std::string>();
	user.salt = row[db::user::SALT].as<std::string>();
	return user;
}

}
