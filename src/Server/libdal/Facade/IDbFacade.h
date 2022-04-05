#pragma once

#include <string>
#include <vector>
#include <pqxx/pqxx>

#include "Types.h"

#include "DTOs/User.h"
#include "DTOs/Product.h"
#include "DTOs/ProductCategory.h"
#include "DTOs/Income.h"
#include "DTOs/IncomeCategory.h"
#include "DTOs/List.h"
#include "DTOs/ListState.h"
#include "DTOs/Statistics.h"
#include "DTOs/IncomeCategory.h"

namespace db
{
class IDbFacade
{
public:
	using Ptr = std::unique_ptr<IDbFacade>;

	virtual ~IDbFacade() {}

	virtual std::optional<IdType> AddUser(const User& user) = 0;
	virtual std::optional<User> GetUserById(IdType id) = 0;
	virtual std::optional<User> GetUserByLogin(const std::string& login) = 0;
	virtual bool UpdateUser(const User& user) = 0;
	virtual bool RemoveUser(IdType id) = 0;

	virtual std::optional<IdType> AddProduct(const Product& product) = 0;
	virtual std::optional<Product> GetProductById(IdType id) = 0;
	virtual std::vector<Product> GetProductsForList(IdType list_id) = 0;
	virtual bool UpdateProduct(const Product& product) = 0;
	virtual bool RemoveProduct(IdType id) = 0;

	virtual std::optional<IdType> AddIncome(const Income& income) = 0;
	virtual std::optional<Income> GetIncomeById(const IdType& id) = 0;
	virtual std::vector<Income> GetAllIncomes(const IdType& user_id) = 0;
	virtual bool UpdateIncome(const Income& income) = 0;
	virtual bool RemoveIncome(const IdType& id) = 0;

	virtual std::optional<IdType> AddList(const List& list) = 0;
	virtual std::optional<List> GetListById(const IdType& id) = 0;
	virtual std::vector<List> GetAllLists(const IdType& user_id) = 0;
	virtual bool UpdateList(const List& list_) = 0;
	virtual bool RemoveList(const IdType& id) = 0;

	virtual std::optional<ListState> GetListStateById(const IdType& list_state_id) = 0;
	virtual std::vector<ListState> GetAllListStates() = 0;

	virtual Money CalculateBalanceForUser(IdType user_id) = 0;
	virtual Money CalculatePlannedBalanceForUser(IdType user_id) = 0;

	virtual bool CanUserEditList(IdType user_id, IdType list_id) = 0;
	virtual bool CanUserEditProduct(IdType user_id, IdType product_id) = 0;
	virtual bool CanUserEditIncome(IdType user_id, IdType income_id) = 0;

	virtual std::vector<Product> GetDailyList(IdType user_id) = 0;

	virtual std::vector<ExpensePerCategory> ExpensesPerCategory(IdType user_id) = 0;
	virtual std::vector<ExpensePercentagePerCategory> ExpensesPercentagePerCategory(IdType user_id) = 0;
	virtual std::vector<ExpensePerDay> ExpensesDynamics(IdType user_id) = 0;

	virtual std::vector<IncomePerCategory> IncomesPerCategory(IdType user_id) = 0;
	virtual std::vector<IncomePercentagePerCategory> IncomesPercentagePerCategory(IdType user_id) = 0;
	virtual std::vector<IncomePerDay> IncomesDynamics(IdType user_id) = 0;

	virtual std::optional<IncomeCategory> GetIncomeCategoryById(IdType id) = 0;
	virtual std::vector<IncomeCategory> GetAllIncomeCategories(IdType user_id) = 0;
	virtual std::optional<IdType> AddIncomeCategory(const IncomeCategory& category) = 0;
	virtual bool UpdateIncomeCategory(const IncomeCategory& category) = 0;
	virtual bool RemoveIncomeCategory(IdType id) = 0;
	virtual bool CanUserEditIncomeCategory(IdType user_id, IdType category_id) = 0;

	virtual std::optional<ProductCategory> GetProductCategoryById(IdType id) = 0;
	virtual std::vector<ProductCategory> GetAllProductCategories(IdType user_id) = 0;
	virtual std::optional<IdType> AddProductCategory(const ProductCategory& category) = 0;
	virtual bool UpdateProductCategory(const ProductCategory& category) = 0;
	virtual bool RemoveProductCategory(IdType id) = 0;
	virtual bool CanUserEditProductCategory(IdType user_id, IdType category_id) = 0;

};
}
