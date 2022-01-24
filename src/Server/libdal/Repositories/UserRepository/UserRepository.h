#pragma once

#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "DTOs/User.h"

class UserRepository
{
public:
	UserRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const User& user);
	std::optional<User> GetById(IdType id);
	std::optional<User> GetByLogin(const std::string& login);
	bool Update(const User& user);
	bool Remove(IdType id);
private:
	static User UserFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
