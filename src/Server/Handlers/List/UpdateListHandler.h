#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/List.h"

class UpdateListHandler : public AuthorizedHandler
{
public:
	UpdateListHandler(IDbFacade::Ptr facade);
	virtual ~UpdateListHandler(){};

	Net::Response AuthHandle(const Net::Request& request) override;

	class JSONParser
	{
	public:
		List Parser(const QJsonObject& payload);
	};

private:
	JSONParser m_parser;
};
