#include "dbfacade.h"

DbFacade::DbFacade(const std::string& connection_string) : m_connection(connection_string), m_users(m_connection)
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
