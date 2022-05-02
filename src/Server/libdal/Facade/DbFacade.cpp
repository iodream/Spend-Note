#include "DbFacade.h"

namespace db
{

DbFacade::DbFacade(const std::string& connection_string)
		: m_connection(connection_string)
		, m_users(m_connection)
		, m_products(m_connection)
		, m_product_categories(m_connection)
		, m_incomes(m_connection)
		, m_lists(m_connection)
		, m_list_states(m_connection)
		, m_income_categories(m_connection)
		, m_balance_repository(m_connection)
		, m_statistics(m_connection)
		, m_recommendation(m_connection)
		, m_periodic_products(m_connection)
{
}

std::optional<IdType> DbFacade::AddUser(const User &user)
{
	return m_users.Add(user);
}

std::optional<User> DbFacade::GetUserById(IdType id)
{
	return m_users.GetById(id);
}

std::optional<User> DbFacade::GetUserByLogin(const std::string& login)
{
	return m_users.GetByLogin(login);
}

bool DbFacade::UpdateUser(const User &user)
{
	return m_users.Update(user);
}

bool DbFacade::RemoveUser(IdType id)
{
	return m_users.Remove(id);
}


std::optional<IdType> DbFacade::AddProduct(const Product& product)
{
	return m_products.Add(product);
}

std::optional<Product> DbFacade::GetProductById(IdType id)
{
	return m_products.GetById(id);
}

std::vector<Product> DbFacade::GetProductsForList(IdType list_id)
{
	return m_products.GetByListId(list_id);
}

bool DbFacade::UpdateProduct(const Product& product)
{
	return m_products.Update(product);
}

bool DbFacade::RemoveProduct(IdType id)
{
	return m_products.Remove(id);
}

std::optional<IdType> DbFacade::AddIncome(const Income& income)
{
	return m_incomes.Add(income);
}

std::optional<Income> DbFacade::GetIncomeById(const IdType& id)
{
	return m_incomes.GetIncome(id);
}

std::vector<Income> DbFacade::GetAllIncomes(const IdType& user_id)
{
	return m_incomes.GetAllIncomes(user_id);
}

bool DbFacade::UpdateIncome(const Income& income)
{
	return m_incomes.Update(income);
}

bool DbFacade::RemoveIncome(const IdType& id)
{
	return m_incomes.Remove(id);
}

std::optional<IdType>  DbFacade::AddList(const List& list)
{
	return m_lists.AddList(list);
}

std::optional<List> DbFacade::GetListById(const IdType& id)
{
	return m_lists.GetList(id);
}

std::vector<List> DbFacade::GetAllLists(const IdType& user_id)
{
	return m_lists.GetAllLists(user_id);
}

bool DbFacade::UpdateList(const List& list)
{
	return m_lists.Update(list);
}

bool DbFacade::RemoveList(const IdType& id)
{
	return m_lists.Remove(id);
}

std::optional<ListState> DbFacade::GetListStateById(const IdType& list_state_id)
{
	return m_list_states.GetById(list_state_id);
}

std::vector<ListState> DbFacade::GetAllListStates()
{
	return m_list_states.GetAll();
}


Money DbFacade::CalculateBalanceForUser(IdType user_id)
{
	return m_balance_repository.CalculateBalance(user_id);
}

Money DbFacade::CalculatePlannedBalanceForUser(IdType user_id)
{
	return m_balance_repository.CalculatePlannedBalance(user_id);
}

bool DbFacade::CanUserEditList(IdType user_id, IdType list_id)
{
	return m_lists.CanUserEditList(user_id, list_id);
}

bool DbFacade::CanUserEditProduct(IdType user_id, IdType product_id)
{
	return m_products.CanUserEditProduct(user_id, product_id);
}

bool DbFacade::CanUserEditIncome(IdType user_id, IdType income_id)
{
	return m_incomes.CanUserEditIncome(user_id, income_id);
}

bool DbFacade::CanUserEditPeriodicProduct(IdType user_id, IdType product_id)
{
	return m_periodic_products.CanUserEditProduct(user_id, product_id);
}

std::vector<Product> DbFacade::GetDailyList(IdType user_id)
{
	return m_products.GetDailyList(user_id);
}

std::vector<ExpensePerCategory> DbFacade::ExpensesPerCategory(IdType user_id, Period period)
{
	return m_statistics.ExpensesPerCategory(user_id, period);
}

std::vector<ExpensePercentagePerCategory> DbFacade::ExpensesPercentagePerCategory(IdType user_id, Period period)
{
	return m_statistics.ExpensesPercentagePerCategory(user_id, period);
}

std::vector<ExpensePerDay> DbFacade::ExpensesDynamics(IdType user_id, Period period)
{
	return m_statistics.ExpensesDynamics(user_id, period);
}

std::vector<IncomePerCategory> DbFacade::IncomesPerCategory(IdType user_id, Period period)
{
	return m_statistics.IncomesPerCategory(user_id, period);
}

std::vector<IncomePercentagePerCategory> DbFacade::IncomesPercentagePerCategory(IdType user_id, Period period)
{
	return m_statistics.IncomesPercentagePerCategory(user_id, period);
}

std::vector<IncomePerDay> DbFacade::IncomesDynamics(IdType user_id, Period period)
{
	return m_statistics.IncomesDynamics(user_id, period);
}

std::optional<IncomeCategory> DbFacade::GetIncomeCategoryById(IdType id)
{
	return m_income_categories.GetById(id);
}

std::vector<IncomeCategory> DbFacade::GetAllIncomeCategories(IdType user_id)
{
	return m_income_categories.GetAll(user_id);
}

std::optional<IdType> DbFacade::AddIncomeCategory(const IncomeCategory& category)
{
	return m_income_categories.Add(category);
}

bool DbFacade::UpdateIncomeCategory(const IncomeCategory& category)
{
	return m_income_categories.Update(category);
}

bool DbFacade::RemoveIncomeCategory(IdType id)
{
	return m_income_categories.Remove(id);
}

bool DbFacade::CanUserEditIncomeCategory(IdType user_id, IdType category_id)
{
	return m_income_categories.CanUserEditIncomeCategory(user_id, category_id);
}
  
std::optional<ProductCategory> DbFacade::GetProductCategoryById(IdType id)
{
	return m_product_categories.GetById(id);
}

std::vector<ProductCategory> DbFacade::GetAllProductCategories(IdType user_id)
{
	return m_product_categories.GetAll(user_id);
}

std::optional<IdType> DbFacade::AddProductCategory(const ProductCategory& category)
{
	return m_product_categories.Add(category);
}

bool DbFacade::UpdateProductCategory(const ProductCategory& category)
{
	return m_product_categories.Update(category);
}

bool DbFacade::RemoveProductCategory(IdType id)
{
	return m_product_categories.Remove(id);
}

bool DbFacade::CanUserEditProductCategory(IdType user_id, IdType category_id)
{
	return m_product_categories.CanUserEditProductCategory(user_id, category_id);
}

Product DbFacade::GetRecommendation(const IdType &user_id)
{
	return m_recommendation.GetRecommendation(user_id);
}

std::optional<IdType> DbFacade::AddPeriodicProduct(const PeriodicProduct& product)
{
	return m_periodic_products.Add(product);
}

std::optional<PeriodicProduct> DbFacade::GetPeriodicProductById(IdType id)
{
	return m_periodic_products.GetById(id);
}

std::vector<PeriodicProduct> DbFacade::GetPeriodicProductsForList(IdType list_id)
{
	return m_periodic_products.GetByListId(list_id);
}

bool DbFacade::UpdatePeriodicProduct(const PeriodicProduct& product)
{
	return m_periodic_products.Update(product);
}

bool DbFacade::RemovePeriodicProduct(IdType id)
{
	return m_periodic_products.Remove(id);
}

}
