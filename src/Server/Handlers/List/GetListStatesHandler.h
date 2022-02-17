#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/ListState.h"

class GetListStatesHandler : public AuthorizedHandler
{
public:
	GetListStatesHandler();
	virtual ~GetListStatesHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ListStatesJSONFormatter m_formatter;
};
