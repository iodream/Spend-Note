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

User UserRepository::GetById(IdType id)
{
	pqxx::nontransaction w(m_database_connection);
	pqxx::row user = w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + ID_FIELD + " = " + w.quote(id) + ";");

	return User {user[ID_FIELD].as<int>(), user[LOGIN_FIELD].as<std::string>(), user[PASSWORD_FIELD].as<std::string>()};
}

User UserRepository::GetByLogin(const std::string& login)
{
	pqxx::nontransaction w(m_database_connection);
	pqxx::row user = w.exec1("SELECT * FROM " + TABLE_NAME + " WHERE " + LOGIN_FIELD + " = " + w.quote(login) + ";");

	return User {user[ID_FIELD].as<int>(), user[LOGIN_FIELD].as<std::string>(), user[PASSWORD_FIELD].as<std::string>()};
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
