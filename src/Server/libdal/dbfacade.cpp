#include "dbfacade.h"

DbFacade::DbFacade(const std::string& connection_string) : m_connection(connection_string), m_users(m_connection)
{

}

void DbFacade::AddUser(const User &user)
{
	m_users.Add(user);
}

User DbFacade::GetUserById(int id)
{
	return m_users.GetById(id);
}

User DbFacade::GetUserByLogin(const std::string& login)
{
	return m_users.GetByLogin(login);
}

void DbFacade::UpdateUser(const User &user)
{
	m_users.Update(user);
}

void DbFacade::RemoveUser(int id)
{
	m_users.Remove(id);
}
