#include "dbfacade.h"

DbFacade::DbFacade(const std::string& connection_string) : m_connection(connection_string), m_users(m_connection),
                                                           m_incomes(m_connection), m_lists(m_connection)
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

void DbFacade::RemuveIncome(const IdType &id)
{
    m_incomes.Remuve(id);
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

void DbFacade::RemuveList(const IdType &id)
{
    m_lists.Remuve(id);
}






















