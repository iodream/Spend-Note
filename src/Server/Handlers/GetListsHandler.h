#pragma once

#include <string>
#include <memory>
#include <utility>

#include "AuthorizedHandler.h"
#include "../libdal/DTOs/List.h"

class GetListsHandler : public AuthorizedHandler
{
	class JSONFormatter
	{
	public:
		using DTOItem = std::pair<const List&, std::string>;

		using DTO = std::vector<DTOItem>;

		QJsonDocument Format(const DTO& dto);
	};
public:
	GetListsHandler(IDbFacade::Ptr facade);
	virtual ~GetListsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONFormatter m_formatter{};
};
