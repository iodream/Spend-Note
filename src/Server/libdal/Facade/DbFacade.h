#pragma once

#include <string>
#include <pqxx/pqxx>
#include "IDbFacade.h"
#include "Repositories/UserRepository/UserRepository.h"
#include "Repositories/ProductRepository/ProductRepository.h"

class DbFacade : public IDbFacade
{
public:
	DbFacade(const std::string& connection_string);

	void AddUser(const User &user) override;
	std::optional<User> GetUserById(IdType id) override;
	std::optional<User> GetUserByLogin(const std::string& login) override;
	void UpdateUser(const User &user) override;
	void RemoveUser(IdType id) override;

	void AddProduct(const Product& product) override;
	std::optional<Product> GetProductById(IdType id) override;
	std::vector<Product> GetProductsForList(IdType list_id) override;
	void UpdateProduct(const Product& user) override;
	void RemoveProduct(IdType id) override;

private:
	pqxx::connection m_connection;

	UserRepository m_users;
	ProductRepository m_products;
};
