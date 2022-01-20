#include "dbfacade.h"

DbFacade::DbFacade(const std::string& connection_string) : m_connection(connection_string), m_users(m_connection),
														   m_incomes(m_connection), m_lists(m_connection),
														   m_list_states(m_connection), m_income_categories(m_connection)

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

void DbFacade::AddIncome(const Income &income)
{
    m_incomes.Add(income);
}

std::optional<Income> DbFacade::GetIncomeById(const IdType &id)
{
    return m_incomes.GetIncome(id);
}

void DbFacade::UpdateIncome(const Income &income)
{
    m_incomes.Update(income);
}

void DbFacade::RemoveIncome(const IdType &id)
{
    m_incomes.Remove(id);
}

void DbFacade::AddList(const List &list_)
{
    m_lists.AddList(list_);
}

std::optional<List> DbFacade::GetListById(const IdType &id)
{
    return m_lists.GetList(id);
}

void DbFacade::UpdateList(const List &list_)
{
    m_lists.Update(list_);
}

void DbFacade::RemoveList(const IdType &id)
{
    m_lists.Remove(id);
}

std::optional<std::vector<Income>> DbFacade::GetAllIncomes(const IdType& id)
{
    return m_incomes.GetAllIncomes(id);
}

std::optional<std::vector<List>> DbFacade::GetAllLists(const idType& id)
{
	return m_lists.GetAllLists(id);
}

std::optional<ListState> DbFacade::GetListCategoryById(const idType& list_state_id)
{
	return m_list_states.GetById(list_state_id);
}

std::vector<ListState> DbFacade::GetListCategoriesAll()
{
	return m_list_states.GetAll();
}

std::optional<IncomeCategory> DbFacade::GetIncomeCategoryById(const idType& category_id)
{
	return m_income_categories.GetById(category_id);
}

std::vector<IncomeCategory> DbFacade::GetIncomeCategoriesAll()
{
	return m_income_categories.GetAll();
}

