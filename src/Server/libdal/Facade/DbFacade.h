#pragma once

#include <string>
#include "IDbFacade.h"
#include "Repositories/UserRepository/UserRepository.h"
#include "Repositories/ProductRepository/ProductRepository.h"
#include "Repositories/ProductCategoryRepository/ProductCategoryRepository.h"
#include "Repositories/IncomeCategoryRepository/IncomeCategoryRepository.h"
#include "Repositories/IncomeRepository/IncomeRepository.h"
#include "Repositories/ListRepository/ListRepository.h"
#include "Repositories/ListStateRepository/ListStateRepository.h"
#include "Repositories/BalanceRepository/BalanceRepository.h"
#include "Repositories/StatisticsRepository/StatisticsRepository.h"
#include "Repositories/RecommendationRepository/RecommendationRepository.h"
#include "Repositories/PeriodicProductRepository/PeriodicProductRepository.h"

namespace db
{
class DbFacade : public IDbFacade
{
public:
	DbFacade(const std::string& connection_string);
	virtual ~DbFacade() override {}

	std::optional<IdType> AddUser(const User &user) override;
	std::optional<User> GetUserById(IdType id) override;
	std::optional<User> GetUserByLogin(const std::string& login) override;
	bool UpdateUser(const User &user) override;
	bool RemoveUser(IdType id) override;

	std::optional<IdType> AddProduct(const Product& product) override;
	std::optional<Product> GetProductById(IdType id) override;
	std::vector<Product> GetProductsForList(IdType list_id) override;
	bool UpdateProduct(const Product& user) override;
	bool RemoveProduct(IdType id) override;

	std::optional<IdType> AddIncome(const Income& income) override;
	std::optional<Income> GetIncomeById(const IdType& id) override;
	std::vector<Income> GetAllIncomes(const IdType& user_id) override;
	bool UpdateIncome(const Income& income) override;
	bool RemoveIncome(const IdType& id) override;

	std::optional<IdType> AddList(const List& list) override;
	std::optional<List> GetListById(const IdType& id) override;
	std::vector<List> GetAllLists(const IdType& user_id) override;
	bool UpdateList(const List& list_) override;
	bool RemoveList(const IdType& id) override;

	std::optional<ListState> GetListStateById(const IdType& list_state_id) override;
	std::vector<ListState> GetAllListStates() override;

	Money CalculateBalanceForUser(IdType user_id) override;
	Money CalculatePlannedBalanceForUser(IdType user_id) override;

	bool CanUserEditList(IdType user_id, IdType list_id) override;
	bool CanUserEditProduct(IdType user_id, IdType product_id) override;
	bool CanUserEditIncome(IdType user_id, IdType income_id) override;

	std::vector<Product> GetDailyList(IdType user_id) override;

	std::vector<ExpensePerCategory> ExpensesPerCategory(IdType user_id, Period period) override;
	std::vector<ExpensePercentagePerCategory> ExpensesPercentagePerCategory(IdType user_id, Period period) override;
	std::vector<ExpensePerDay> ExpensesDynamics(IdType user_id, Period period) override;

	std::vector<IncomePerCategory> IncomesPerCategory(IdType user_id, Period period) override;
	std::vector<IncomePercentagePerCategory> IncomesPercentagePerCategory(IdType user_id, Period period) override;
	std::vector<IncomePerDay> IncomesDynamics(IdType user_id, Period period) override;

	std::optional<IncomeCategory> GetIncomeCategoryById(IdType id) override;
	std::vector<IncomeCategory> GetAllIncomeCategories(IdType user_id) override;
	std::optional<IdType> AddIncomeCategory(const IncomeCategory& category) override;
	bool UpdateIncomeCategory(const IncomeCategory& category) override;
	bool RemoveIncomeCategory(IdType id) override;
	bool CanUserEditIncomeCategory(IdType user_id, IdType category_id) override;

	std::optional<ProductCategory> GetProductCategoryById(IdType id) override;
	std::vector<ProductCategory> GetAllProductCategories(IdType user_id) override;
	std::optional<IdType> AddProductCategory(const ProductCategory& category) override;
	bool UpdateProductCategory(const ProductCategory& category) override;
	bool RemoveProductCategory(IdType id) override;
	bool CanUserEditProductCategory(IdType user_id, IdType category_id) override;

	Product GetRecommendation(const IdType& user_id) override;

	std::optional<IdType> AddPeriodicProduct(const PeriodicProduct& product) override;
	std::optional<PeriodicProduct> GetPeriodicProductById(IdType id) override;
	std::vector<PeriodicProduct> GetPeriodicProductsForList(IdType list_id) override;
	bool UpdatePeriodicProduct(const PeriodicProduct& product) override;
	bool RemovePeriodicProduct(IdType id) override;

private:
	pqxx::connection m_connection;

	UserRepository m_users;
	ProductRepository m_products;
	ProductCategoryRepository m_product_categories;
	IncomeRepository m_incomes;
	IncomeCategoryRepository m_income_categories;
	ListRepository m_lists;
	ListStateRepository m_list_states;
	BalanceRepository m_balance_repository;
	StatisticsRepository m_statistics;
	RecommendationRepository m_recommendation;
	PeriodicProductRepository m_periodic_products;
};
}
