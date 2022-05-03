#include "UserRepository.h"

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
				db::user::EMAIL + ", " +
				db::user::PASSWORD + ", " +
				db::user::SALT + ", " +
				user::VERIFIED +
			") VALUES (" +
				w.quote(user.email) + ", " +
				w.quote(user.password_hash) + ", " +
				w.quote(user.salt) + ")" +
        w.quote(user.verified) + ")" +
			" RETURNING " + db::user::ID + ";");

		w.commit();

		auto id_row = id_rows.front();
		return id_row[user::ID].as<IdType>();
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
			"SELECT " + db::user::ID + ", " + db::user::EMAIL + ", " + db::user::PASSWORD + ", " + db::user::SALT ", " + db::user::VERIFIED +
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

std::optional<User> UserRepository::GetByEmail(const std::string& email)
{
	try
	{
		pqxx::nontransaction w(m_database_connection);
		pqxx::result user_rows = w.exec(
			"SELECT " + db::user::ID + ", " + db::user::EMAIL + ", " + db::user::PASSWORD + ", " + db::user::SALT + ", " + db::user::VERIFIED +
			" FROM " + db::user::TABLE_NAME +
			" WHERE " + db::user::EMAIL + " = " + w.quote(email) + ";");

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

		auto result = w.exec("SELECT " + user::ID + " FROM  " + user::TABLE_NAME + " WHERE " + user::ID + " = " + w.quote(user.id));
		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + user::TABLE_NAME +
			" SET " +
				user::EMAIL + " = " + w.quote(user.email) + ", " +
				user::PASSWORD + " = " + w.quote(user.password) + ", " +
				user::VERIFIED + " = " + w.quote(user.verified) +
			" WHERE " + user::ID + " = " + w.quote(user.id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool UserRepository::UpdatePassword(const IdType user_id, const std::string& password)
{
	try
	{
		pqxx::work w(m_database_connection);

		auto result = w.exec("SELECT " + user::ID +
			" FROM  " + user::TABLE_NAME +
			" WHERE " + user::ID + " = " + w.quote(user_id));

		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + user::TABLE_NAME +
			" SET " +
			user::PASSWORD + " = " + w.quote(password) +
			" WHERE " + user::ID + " = " + w.quote(user_id) + ";");
		w.commit();
	}
	catch(const pqxx::failure& e)
	{
		throw DatabaseFailure(e.what());
	}
	return true;
}

bool UserRepository::UpdateVerification(IdType id)
{
	try
	{
		pqxx::work w(m_database_connection);

		auto result = w.exec("SELECT " + user::ID + " FROM  " + user::TABLE_NAME + " WHERE " + user::ID + " = " + w.quote(id));
		if (result.empty())
		{
			return false;
		}

		w.exec0(
			"UPDATE " + user::TABLE_NAME +
			" SET " + user::VERIFIED + " = " + w.quote(true) +
			" WHERE " + user::ID + " = " + w.quote(id) + ";");

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

	user.id = row[db::user::ID].as<IdType>();
	user.email = row[db::user::EMAIL].as<std::string>();
	user.password_hash = row[db::user::PASSWORD].as<std::string>();
	user.salt = row[db::user::SALT].as<std::string>();
  user.verified = row[db::user::VERIFIED].as<bool>();

	return user;
}

}
