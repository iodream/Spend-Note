#pragma once

#include <string>
#include <vector>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"
#include "../libdal/Facade/IDbFacade.h"


class UpdateProductHandler : public AuthorizedHandler
{
public:
	UpdateProductHandler();
	virtual ~UpdateProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

	class JSONParser
	{
	public:
		Product Parse(const QJsonObject& payload);
	};

private:
	JSONParser m_parser;
};
