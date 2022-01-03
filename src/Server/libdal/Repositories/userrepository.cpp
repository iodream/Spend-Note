#include "userrepository.h"

UserRepository::UserRepository(pqxx::connection &db_connection) : db_connection(db_connection)
{

}

void UserRepository::Add(const User &user)
{
    pqxx::work w(db_connection);
    w.exec1("INSERT INTO Users (login, pass) VALUES (" + w.quote(user.login) + ", " + w.quote(user.pass) + ");");
    w.commit();
}

User UserRepository::GetById(int id)
{
    pqxx::work w(db_connection);
    pqxx::row user = w.exec1("SELECT * FROM Users WHERE id = " + w.quote(id) + ";");
    w.commit();

    return User {user["id"].as<int>(), user["login"].as<std::string>(), user["pass"].as<std::string>()};
}

User UserRepository::GetByLogin(const std::string& login)
{
    pqxx::work w(db_connection);
    pqxx::row user = w.exec1("SELECT * FROM Users WHERE login = " + w.quote(login) + ";");
    w.commit();

    return User {user["id"].as<int>(), user["login"].as<std::string>(), user["pass"].as<std::string>()};
}

void UserRepository::Update(const User &user)
{
    pqxx::work w(db_connection);
    w.exec1("UPDATE table_name SET login = " + w.quote(user.login) + ", pass = " + w.quote(user.pass) + ", ... WHERE id = " + w.quote(user.id) + ";");
    w.commit();
}

void UserRepository::Remove(int id)
{
    pqxx::work w(db_connection);
    w.exec1("DELETE FROM Users WHERE id = " + w.quote(id) + ";");
    w.commit();
}
