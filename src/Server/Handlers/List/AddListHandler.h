#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/List.h"

class AddListHandler : public AuthorizedHandler
{
public:
	AddListHandler();
	virtual ~AddListHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	db::List ToDBList(const List& list);
private:
	ListJSONParser m_parser{};
	ListIdJSONFormatter m_formatter{};
};
