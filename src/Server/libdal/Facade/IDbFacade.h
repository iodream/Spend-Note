#pragma once

#include <string>
#include <vector>

#include "DTOs/User.h"
#include "DTOs/Product.h"

class IDbFacade
{
public:
	using Ptr = std::shared_ptr<IDbFacade>;

	virtual void AddUser(const User& user) = 0;
	virtual std::optional<User> GetUserById(IdType id) = 0;
	virtual std::optional<User> GetUserByLogin(const std::string& login) = 0;
	virtual void UpdateUser(const User& user) = 0;
	virtual void RemoveUser(IdType id) = 0;

	virtual void AddProduct(const Product& product) = 0;
	virtual std::optional<Product> GetProductById(IdType id) = 0;
	virtual std::vector<Product> GetProductsForList(IdType list_id) = 0;
	virtual void UpdateProduct(const Product& user) = 0;
	virtual void RemoveProduct(IdType id) = 0;
};
