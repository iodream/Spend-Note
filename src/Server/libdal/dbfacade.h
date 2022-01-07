#pragma once

#include <string>
#include <pqxx/pqxx>
#include "idbfacade.h"
#include "Repositories/userrepository.h"


class DbFacade : public IDbFacade
{
public:
	DbFacade(const std::string& connection_string);

	void AddUser(const User &user) override;
	User GetUserById(IdType id) override;
	User GetUserByLogin(const std::string& login) override;
	void UpdateUser(const User &user) override;
	void RemoveUser(IdType id) override;

private:
	pqxx::connection m_connection;
	UserRepository m_users;
};
