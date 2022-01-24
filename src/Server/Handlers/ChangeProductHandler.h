#pragma once

#include <string>
#include <vector>

#include "AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"
#include "../libdal/Facade/IDbFacade.h"

using IdType= long long int;

class ChangeProductHandler : public AuthorizedHandler
{
	ChangeProductHandler(IDbFacade::Ptr facade);
	virtual ~ChangeProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

public:
	class JSONParser
	{
	public:
		using DTO = Product;
		DTO Parse(const QJsonDocument& payload);
	};

private:
	JSONParser m_parser;
};
