#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"

class RemoveProductHandler : public AuthorizedHandler
{
	class JSONParser
	{
	public:
		struct Product{
			IdType id;
		};

		Product Parse(const QJsonDocument& payload);
	};
public:
	RemoveProductHandler(IDbFacade::Ptr facade);
	virtual ~RemoveProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONParser m_parser{};
};
