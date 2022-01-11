#include "userrepository.h"
#include <string_view>

namespace
{
	const std::string& TABLE_NAME = "User";
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
	w.exec0("INSERT INTO " + TABLE_NAME + " (" + LOGIN_FIELD + ", " + PASSWORD_FIELD + ") VALUES (" + w.quote(user.login) + ", " + w.quote(user.password) + ");");
    w.commit();
}

std::optional<User> UserRepository::GetById(IdType id)
{
	pqxx::nontransaction w(m_database_connection);
	pqxx::result user_rows = w.exec(
			"SELECT " + ID_FIELD + ", " + LOGIN_FIELD + ", " + PASSWORD_FIELD +
			" FROM " + w.quote_name(TABLE_NAME) +
			" WHERE " + w.quote_name(ID_FIELD) + " = " + w.quote(id) + ";");

	if (user_rows.empty())
	{
		return std::nullopt;
	}

	return UserFromRow(user_rows.front());
}

std::optional<User> UserRepository::GetByLogin(const std::string& login)
{
	pqxx::nontransaction w(m_database_connection);
	pqxx::result user_rows = w.exec(
			"SELECT " + ID_FIELD + ", " + LOGIN_FIELD + ", " + PASSWORD_FIELD +
			" FROM " + w.quote_name(TABLE_NAME) +
			" WHERE " + w.quote_name(LOGIN_FIELD) + " = " + w.quote(login) + ";");

	if (user_rows.empty())
	{
		return std::nullopt;
	}

	return UserFromRow(user_rows.front());
}

void UserRepository::Update(const User &user)
{
	pqxx::work w(m_database_connection);
	w.exec0("UPDATE " + TABLE_NAME + " SET " + LOGIN_FIELD + " = " + w.quote(user.login) + ", " + PASSWORD_FIELD + " = " + w.quote(user.password) + " WHERE " + ID_FIELD + " = " + w.quote(user.id) + ";");
    w.commit();
}

void UserRepository::Remove(IdType id)
{
	pqxx::work w(m_database_connection);
	w.exec0("DELETE FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");
	w.commit();
}

User UserRepository::UserFromRow(const pqxx::row& row)
{
	User user;
	user.id = row[ID_FIELD].as<int>();
	user.login = row[LOGIN_FIELD].as<std::string>();
	user.password = row[PASSWORD_FIELD].as<std::string>();

	return user;
}
