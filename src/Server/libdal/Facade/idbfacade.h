#pragma once

#include <string>
#include "DTOs/User.h"

class IDbFacade
{
public:
	using Ptr = std::shared_ptr<IDbFacade>;

	virtual void AddUser(const User& user) = 0;
	virtual std::optional<User> GetUserById(IdType id) = 0;
	virtual std::optional<User> GetUserByLogin(const std::string& login) = 0;
	virtual void UpdateUser(const User& user) = 0;
	virtual void RemoveUser(IdType id) = 0;

    virtual void AddIncome(const Income& income) = 0;
    virtual std::optional<Income> GetIncomeById(const IdType& id) = 0;
    virtual void UpdateIncome(const Income& income) = 0;
    virtual void RemuveIncome(const IdType& id) = 0;

    virtual void AddList(const List& list_) = 0;
    virtual std::optional<List> GetListById(const IdType& id) = 0;
    virtual void UpdateList(const List& list_) = 0;
    virtual void RemuveList(const IdType& id) = 0;

};
