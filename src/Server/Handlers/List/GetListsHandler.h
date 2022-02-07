#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/List.h"

class GetListsHandler : public AuthorizedHandler
{
	using ListItem = std::pair<const db::List&, const db::ListState&>;
	using Lists = std::vector<ListItem>;
public:
	GetListsHandler();
	virtual ~GetListsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	std::vector<List> ToNetLists(const Lists& lists);
private:
	ListsJSONFormatter m_formatter;
};
