#pragma once

#include <string>
#include "IDbFacade.h"
#include "Repositories/UserRepository/UserRepository.h"
#include "Repositories/ProductRepository/ProductRepository.h"
#include "Repositories/ProductCategoryRepository/ProductCategoryRepository.h"
#include "Repositories/IncomeCategoryRepository/IncomeCategoryRepository.h"
#include "Repositories/IncomeRepository/IncomeRepository.h"
#include"Repositories/ListRepository/ListRepository.h"
#include "Repositories/ListStateRepository/ListStateRepository.h"

class DbFacade : public IDbFacade
{
public:
	DbFacade(const std::string& connection_string);
	virtual ~DbFacade() override {}

	void AddUser(const User &user) override;
	std::optional<User> GetUserById(IdType id) override;
	std::optional<User> GetUserByLogin(const std::string& login) override;
	void UpdateUser(const User &user) override;
	void RemoveUser(IdType id) override;

	std::optional<IdType> AddProduct(const Product& product) override;
	std::optional<Product> GetProductById(IdType id) override;
	std::vector<Product> GetProductsForList(IdType list_id) override;
	void UpdateProduct(const Product& user) override;
	void RemoveProduct(IdType id) override;

	std::optional<ProductCategory> GetProductCategoryById(IdType id) override;
	std::vector<ProductCategory> GetAllProductCategories() override;

	std::optional<IdType> AddIncome(const Income& income) override;
	std::optional<Income> GetIncomeById(const IdType& id) override;
	std::vector<Income> GetAllIncomes(const IdType& user_id) override;
	void UpdateIncome(const Income& income) override;
	void RemoveIncome(const IdType& id) override;

	std::optional<IdType> AddList(const List& list) override;
	std::optional<List> GetListById(const IdType& id) override;
	std::vector<List> GetAllLists(const IdType& user_id) override;
	void UpdateList(const List& list_) override;
	void RemoveList(const IdType& id) override;

	std::optional<IncomeCategory> GetIncomeCategoryById(const IdType& category_id) override;
	std::vector<IncomeCategory> GetAllIncomeCategories() override;

	std::optional<ListState> GetListStateById(const IdType& list_state_id) override;
	std::vector<ListState> GetAllListStates() override;

private:
	pqxx::connection m_connection;

	UserRepository m_users;
	ProductRepository m_products;
	ProductCategoryRepository m_product_categories;
	IncomeRepository m_incomes;
	IncomeCategoryRepository m_income_categories;
	ListRepository m_lists;
	ListStateRepository m_list_states;
};
