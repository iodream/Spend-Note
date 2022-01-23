#pragma once

#include <string>
#include <vector>

#include "AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"
#include "../libdal/Facade/IDbFacade.h"

using IdType= long long int;

class ChangeProductHandler : public AuthorizedHandler
{
	ChangeProductHandler();
	virtual ~ChangeProductHandler() override {}

	Product Parser(const QJsonObject &obj);
	virtual Net::Response AuthHandle(const Net::Request& request) override;

	std::unique_ptr<IDbFacade> m_facade;
};
