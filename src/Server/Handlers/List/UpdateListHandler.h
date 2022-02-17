#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/List.h"

class UpdateListHandler : public AuthorizedHandler
{
public:
	UpdateListHandler();
	virtual ~UpdateListHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ListJSONParser m_parser{};
};
