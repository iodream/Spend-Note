#pragma once

#include <string>
#include <vector>

#include "AuthorizedHandler.h"
#include "../libdal/Facade/IDbFacade.h"
#include "../libdal/DTOs/List.h"

using IdType= long long int;

class GetListsHandler : public AuthorizedHandler
{
	QJsonDocument Format(const std::optional<std::vector<List>>& vector);
	GetListsHandler();
    virtual ~GetListsHandler() override {}
    virtual Net::Response AuthHandle(const Net::Request& request) override;
	std::unique_ptr<IDbFacade> m_facade;
};
