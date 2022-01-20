#pragma once

#include "Repositories/IncomeRepository/IncomeRepository.h"
#include "Repositories/ListRepository/ListRepository.h"
#include "Repositories/UserRepository/UserRepository.h"
#include "Repositories/ListStateRepository/ListStateRepository.h"
#include "Repositories/IncomeCategoryRepository/IncomeCategoryRepository.h"

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
    virtual std::optional<std::vector<Income>> GetAllIncomes(const IdType& id) = 0;
    virtual void UpdateIncome(const Income& income) = 0;
    virtual void RemoveIncome(const IdType& id) = 0;

    virtual void AddList(const List& list_) = 0;
    virtual std::optional<List> GetListById(const IdType& id) = 0;
	virtual std::optional<std::vector<List>> GetAllLists(const idType& id) = 0;
    virtual void UpdateList(const List& list_) = 0;
    virtual void RemoveList(const IdType& id) = 0;

	virtual std::optional<ListState> GetListCategoryById(const idType& list_state_id) = 0;
	virtual std::vector<ListState> GetListCategoriesAll() = 0;

	virtual std::optional<IncomeCategory> GetIncomeCategoryById(const idType& category_id) = 0;
	virtual std::vector<IncomeCategory> GetIncomeCategoriesAll() = 0;

};
