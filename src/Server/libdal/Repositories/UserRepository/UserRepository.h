#pragma once

#include <string>
#include <optional>
#include <pqxx/pqxx>
#include "DTOs/User.h"

namespace db
{
class UserRepository
{
public:
	UserRepository(pqxx::connection& db_connection);

	std::optional<IdType> Add(const User& user);
	std::optional<User> GetById(IdType id);
	std::optional<User> GetByEmail(const std::string& email);
	bool Update(const User& user);
	bool Remove(IdType id);
private:
	static User UserFromRow(const pqxx::row& row);

	pqxx::connection& m_database_connection;
};
}
