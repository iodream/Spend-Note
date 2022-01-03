#pragma once

#include <string>
#include <pqxx/pqxx>
#include "DTOs/User.h"

class UserRepository
{
public:
    UserRepository(pqxx::connection& db_connection);

	void Add(const User& user);
	User GetById(int id);
	User GetByLogin(const std::string& login);
	void Update(const User& user);
	void Remove(int id);
private:
    pqxx::connection& db_connection;
};
