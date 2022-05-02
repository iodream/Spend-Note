#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Product.h"

class AddProductHandler : public AuthorizedHandler
{
public:
	AddProductHandler();
	virtual ~AddProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductJSONParser m_parser{};
	ProductIdJSONFormatter m_formatter{};
};
