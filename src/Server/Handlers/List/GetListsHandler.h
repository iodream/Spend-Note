#pragma once

#include <string>
#include <memory>
#include <utility>

#include "ParserAndFormatter/ListJSONFormatter.h"
#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/List.h"

class GetListsHandler : public AuthorizedHandler
{
	class JSONFormatter
	{
	public:
		using ListItem = std::pair<const List&, std::string>;

		using Lists = std::vector<ListItem>;

		QJsonDocument Format(const Lists& dto);
	};
public:
	GetListsHandler(IDbFacade::Ptr facade);
	virtual ~GetListsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONFormatter m_formatter{};
};
