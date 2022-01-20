#pragma once

#include <string>
#include "idbfacade.h"

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
    std::optional<std::vector<Income>> GetAllIncomes(const IdType& id) override;
    void UpdateIncome(const Income& income) override;
    void RemoveIncome(const IdType& id) override;

    void AddList(const List& list_) override;
    std::optional<List> GetListById(const IdType& id) override;
	std::optional<std::vector<List>> GetAllLists(const idType& id) override;
    void UpdateList(const List& list_) override;
    void RemoveList(const IdType& id) override;

	std::optional<ListState> GetListCategoryById(const idType& list_state_id) override;
	std::vector<ListState> GetListCategoriesAll() override;

	std::optional<IncomeCategory> GetIncomeCategoryById(const idType& category_id) override;
	std::vector<IncomeCategory> GetIncomeCategoriesAll() override;

private:
	pqxx::connection m_connection;
	UserRepository m_users;
    IncomeRepository m_incomes;
    ListRepository m_lists;
	ListStateRepository m_list_states;
	IncomeCategoryRepository m_income_categories;
};
