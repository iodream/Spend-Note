#pragma once

#include <string>
#include "DTOs/User.h"

class IDbFacade
{
public:
	virtual void AddUser(const User& user) = 0;
	virtual User GetUserById(IdType id) = 0;
	virtual User GetUserByLogin(const std::string& login) = 0;
	virtual void UpdateUser(const User& user) = 0;
	virtual void RemoveUser(IdType id) = 0;
};
