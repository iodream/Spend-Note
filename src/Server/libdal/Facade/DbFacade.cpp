#include "DbFacade.h"

DbFacade::DbFacade(const std::string& connection_string) :
		m_connection(connection_string),
		m_users(m_connection),
		m_products(m_connection),
		m_product_categories(m_connection)
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

void DbFacade::UpdateProduct(const Product& user)
{
	m_products.Update(user);
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
