#include "DbFacade.h"

DbFacade::DbFacade(const std::string& connection_string)
		: m_connection(connection_string)
		, m_users(m_connection)
		, m_products(m_connection)
		, m_product_categories(m_connection)
		, m_incomes(m_connection)
		, m_lists(m_connection)
		, m_list_states(m_connection)
		, m_income_categories(m_connection)
{
}

void DbFacade::AddUser(const User &user)
{
	m_users.Add(user);
}

std::optional<User> DbFacade::GetUserById(IdType id)
{
	return m_users.GetById(id);
}

std::optional<User> DbFacade::GetUserByLogin(const std::string& login)
{
	return m_users.GetByLogin(login);
}

void DbFacade::UpdateUser(const User &user)
{
	m_users.Update(user);
}

void DbFacade::RemoveUser(IdType id)
{
	m_users.Remove(id);
}


void DbFacade::AddProduct(const Product& product)
{
	m_products.Add(product);
}

std::optional<Product> DbFacade::GetProductById(IdType id)
{
	return m_products.GetById(id);
}

std::vector<Product> DbFacade::GetProductsForList(IdType list_id)
{
	return m_products.GetByListId(list_id);
}

void DbFacade::UpdateProduct(const Product& product)
{
	m_products.Update(product);
}

void DbFacade::RemoveProduct(IdType id)
{
	m_products.Remove(id);
}


std::optional<ProductCategory> DbFacade::GetProductCategoryById(IdType id)
{
	return m_product_categories.GetById(id);
}

std::vector<ProductCategory> DbFacade::GetAllProductCategories()
{
	return m_product_categories.GetAll();
}

void DbFacade::AddIncome(const Income& income)
{
	m_incomes.Add(income);
}

std::optional<Income> DbFacade::GetIncomeById(const IdType& id)
{
	return m_incomes.GetIncome(id);
}

std::optional<std::vector<Income>> DbFacade::GetAllIncomes(const IdType& user_id)
{
	return m_incomes.GetAllIncomes(user_id);
}

void DbFacade::UpdateIncome(const Income& income)
{
	m_incomes.Update(income);
}

void DbFacade::RemoveIncome(const IdType& id)
{
	m_incomes.Remove(id);
}

void DbFacade::AddList(const List& list)
{
	 m_lists.AddList(list);
}

std::optional<List> DbFacade::GetListById(const IdType& id)
{
	return m_lists.GetList(id);
}

std::vector<List> DbFacade::GetAllLists(const IdType& user_id)
{
	return m_lists.GetAllLists(user_id);
}

void DbFacade::UpdateList(const List& list)
{
	m_lists.Update(list);
}

void DbFacade::RemoveList(const IdType& id)
{
	m_lists.Remove(id);
}

std::optional<IncomeCategory> DbFacade::GetIncomeCategoryById(const IdType& category_id)
{
	return m_income_categories.GetById(category_id);
}

std::vector<IncomeCategory> DbFacade::GetIncomeCategoriesAll()
{
	return m_income_categories.GetAll();
}

std::optional<ListState> DbFacade::GetListStateById(const IdType& list_state_id)
{
	return m_list_states.GetById(list_state_id);
}

std::vector<ListState> DbFacade::GetAllListStates()
{
	return m_list_states.GetAll();
}
