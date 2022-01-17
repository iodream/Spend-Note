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
	std::optional<User> GetUserById(IdType id) override;
	std::optional<User> GetUserByLogin(const std::string& login) override;
	void UpdateUser(const User &user) override;
	void RemoveUser(IdType id) override;

    void AddIncome(const Income& income) override;
    std::optional<Income> GetIncomeById(const IdType& id) override;
    void UpdateIncome(const Income& income) override;
    void RemuveIncome(const IdType& id) override;

    void AddList(const List& list_) override;
    std::optional<List> GetListById(const IdType& id) override;
    void UpdateList(const List& list_) override;
    void RemuveList(const IdType& id) override;

private:
	pqxx::connection m_connection;
	UserRepository m_users;
    IncomeRepository m_incomes;
    ListRepository m_lists;
};
