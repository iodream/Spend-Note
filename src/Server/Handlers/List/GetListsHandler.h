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
public:
	GetListsHandler();
	virtual ~GetListsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ListsJSONFormatter m_formatter;
};
